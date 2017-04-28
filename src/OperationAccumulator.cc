#include <fstream>
#include <iostream>
#include <sstream>

#include "DiffInterface.h"
#include "FileParser.h"
#include "FileSystemInterface.h"
#include "FileWriter.h"
#include "OperationAccumulator.h"

using namespace std;

OperationAccumulator::OperationAccumulator() :
  projectInit(false), projectInitializedThisRun(false), branchChanged(false),
  initialCommitPerformed(false), curCommit("") {
  fileNames[FileName::MAIN_DIR] = ".kil";
  fileNames[FileName::BASIC_INFO] = ".kil/.basicInfo.txt";
  fileNames[FileName::ADDED_FILES] = ".kil/.addedFiles.txt";
  fileNames[FileName::TRACKED_FILES] = ".kil/.trackedFiles.txt";
  fileNames[FileName::COMMIT_DIR] = ".kil/.commits";
}

void OperationAccumulator::initializeProject(const std::string& fileName) {
  projectInit = true;
  projectInitializedThisRun = true;
  projectName = fileName;
  
  branchChanged = true;
  curBranch = "Master";
}

bool OperationAccumulator::alreadyTracked(const string& fileName) const {
  for (string file : trackedFiles) {
    if (fileName == file) {
      return true;
    }
  }

  for (string file : addedFiles) {
    if (fileName == file) {
      return true;
    }
  }

  return false;
}

bool OperationAccumulator::addFile(const string& fileName) {  
  // Do we already have this file
  if (!alreadyTracked(fileName)) {
    addedFiles.push_back(fileName);
    return true;
  }

  return false;
}

void OperationAccumulator::outputTrackedFiles() const {
  string trackedFileConfigFileName = fileNames.at(FileName::TRACKED_FILES);

  ofstream outputStream;
  outputStream.open(trackedFileConfigFileName, fstream::out);

  for (string fileName : trackedFiles) {
    outputStream << fileName << "\n";
  }
  
  outputStream << flush;
  outputStream.close();
}

void OperationAccumulator::outputAddedFiles() const {
  string addedFileConfigFileName = fileNames.at(FileName::ADDED_FILES);

  ofstream outputStream;
  outputStream.open(addedFileConfigFileName, fstream::out);
  
  for (string fileName : addedFiles) {
    outputStream << fileName << "\n";
  }
  
  outputStream << flush;
  outputStream.close();
}

bool OperationAccumulator::outputBasicInfo() const {
  if (FileSystemInterface::createDirectory(fileNames.at(FileName::MAIN_DIR))
      == -1) {
    cout << "Could not initialize project!\n";
    return false;
  }
  
  string basicProjectInfoFileName = fileNames.at(FileName::BASIC_INFO);
  
  ofstream outputStream;
  outputStream.open(basicProjectInfoFileName, fstream::out);

  outputStream << "projName=" << projectName << "\n";
  outputStream << "curBranch=" << curBranch << "\n";
  outputStream << "initialCommit=" << (initialCommitPerformed ? "true" : "false")  << "\n";
  if (initialCommitPerformed) {
    outputStream << "curCommit=" << curCommit.toString() << "\n";
    outputStream << "lastHash=" << CommitHash::getLatestGeneratedHash().toString() << "\n";
  }
  
  outputStream << flush;
  outputStream.close();

  return true;
}

bool OperationAccumulator::readAddedAndTrackedFiles(const string& errorMessage) {
  // read in from the trackedFiles file
  if (!FileSystemInterface::fileExists(fileNames.at(FileName::TRACKED_FILES)) ||
      !FileSystemInterface::fileExists(fileNames.at(FileName::ADDED_FILES))) {
    cout << errorMessage << endl;
    return false;
  }

  vector<string> lines;
  FileParser::readFile(fileNames.at(FileName::TRACKED_FILES), lines);
  for (string fileName : lines) {
    trackedFiles.push_back(fileName);
  }

  lines.clear();
  FileParser::readFile(fileNames.at(FileName::ADDED_FILES), lines);
  for (string fileName : lines) {
    addedFiles.push_back(fileName);
  }

  return true;
}

bool OperationAccumulator::initialize() {
  // try and see if the .kil directory is created
  if (!(FileSystemInterface::fileExists(fileNames.at(FileName::MAIN_DIR)))) {
    return true;
  }

  projectInit = true;

  const string error = "Error! KIL information tampered with or missing!";
  
  // make sure that all of the information that needs to be there, is there
  if (!(FileSystemInterface::fileExists(fileNames.at(FileName::BASIC_INFO)))) {
    cout << error << endl;
    return false;
  }

  vector<string> lines;
  FileParser::readFile(fileNames.at(FileName::BASIC_INFO), lines);

  if (lines.size() < 3) {
    cout << error << endl;
    return false;
  }

  if (lines[0].find("projName=") != 0 || lines[0].substr(9).length() == 0 ||
      lines[1].find("curBranch=") != 0 || lines[1].substr(10).length() == 0 ||
      lines[2].find("initialCommit=") != 0) {
    cout << error << endl;
    return false;
  }

  cout << "issue here" << endl;

  string initialCommitString = lines[2].substr(14);
  
  if (initialCommitString != "true" && initialCommitString != "false") {
    cout << error << endl;
    return false;
  }

  cout << "or how about here" << endl;

  projectName = lines[0].substr(9);
  curBranch = lines[1].substr(10);
  
  initialCommitPerformed = initialCommitString == "true" ? true : false;

  if (initialCommitPerformed) {
    if (lines.size() != 5 || lines[3].find("curCommit=") != 0 ||
	lines[3].substr(10).length() == 0 || lines[4].find("lastHash=") != 0 ||
	lines[4].substr(9).length() == 0) {
      cout << error << endl;
      return false;
    }
    curCommit = CommitHash(lines[3].substr(10));
    CommitHash::setSeed(lines[4].substr(9));
  }

  cout << "even lower" << endl;

  return readAddedAndTrackedFiles(error);
}

void OperationAccumulator::saveState() const {
  if (!projectInit) {
    return;
  }

  if (projectInitializedThisRun) {
    if (!outputBasicInfo()) {
      return;
    }
  }

  outputTrackedFiles();
  outputAddedFiles();
}

bool OperationAccumulator::isInitialized() const {
  return projectInit;
}

string OperationAccumulator::getCurBranchName() const {
  return curBranch;
}

void OperationAccumulator::calculateRemovalsAndDiffs(
    vector<string>& removedFiles, vector<pair<string, FileDiff> >& diffs) const {
  for (const string& trackedFile : trackedFiles) {
    if (FileSystemInterface::fileExists(trackedFile.c_str())) {
      // calculate the location of the previous diff
      // path to version of file in previous commit will be commithash/filepath
      string previousCommitFileName =
	FileSystemInterface::appendPath(fileNames.at(COMMIT_DIR), curCommit.toString());
      previousCommitFileName =
	FileSystemInterface::appendPath(previousCommitFileName, trackedFile);
      FileDiff diff =
	DiffInterface::calculateFileDiff(
	    previousCommitFileName.c_str(), trackedFile.c_str());
      if (!diff.isEmptyDiff()) {
	diffs.push_back(make_pair(trackedFile, diff));
      }
    } else {
      removedFiles.push_back(trackedFile);
    }
  }
}

void OperationAccumulator::writeOutCommit(
    const string& commitMessage, const vector<string>& addedFiles,
    const vector<string>& removedFiles,
    const vector<pair<string, FileDiff> >& diffs) {
    // first, write it out in the pool of diffs
    CommitHash hash;
    curCommit = hash;

    string newCommitDirectoryPath =
      FileSystemInterface::appendPath(fileNames.at(COMMIT_DIR),
				      hash.toString().c_str());

    if (!initialCommitPerformed) {
      vector<string> directories;
      FileSystemInterface::parseDirectoryStructure(newCommitDirectoryPath, directories);
      FileSystemInterface::createDirectories("", directories);
    }
    
    // Create new directory with hash
    FileSystemInterface::createDirectory(newCommitDirectoryPath.c_str());

    ofstream output;
    string newCommitFileName =
      FileSystemInterface::appendPath(newCommitDirectoryPath, hash.toString().c_str());
    output.open((newCommitFileName + ".txt").c_str(), fstream::out);
    output << "commitHash=" << hash.toString() << "\n";
    output << "commitMessage=\"" << commitMessage << "\"\n";

    output << "addedFiles [" << addedFiles.size() << "]\n";
    for (string addedFile : addedFiles) {
        output << addedFile << "\n";
    }

    // now write out the files themselves
    for (const string& newFile : addedFiles) {
      vector<string> directories;
      FileSystemInterface::parseDirectoryStructure(newFile, directories);
      FileSystemInterface::createDirectories(newCommitDirectoryPath, directories);
      vector<string> fileLines;
      FileParser::readFile(newFile.c_str(), fileLines);
      FileWriter::writeFile(
          FileSystemInterface::appendPath(newCommitDirectoryPath, newFile).c_str(),
	                                  fileLines);
    }
    
    // now write out the removed files
    output << "removedFiles [" << removedFiles.size() << "]\n";
    for (string removedFile : removedFiles) {
        output << removedFile << "\n";
    }

    // write out which files have diffs
    output << "diffs [" << diffs.size() << "]\n";
    
    // now write out the diffs
    for (const pair<string, FileDiff>& diffInfo : diffs) {
      vector<string> directories;
      FileSystemInterface::parseDirectoryStructure(diffInfo.first, directories);
      FileSystemInterface::createDirectories(newCommitDirectoryPath, directories);
      diffInfo.second.print(
          FileSystemInterface::appendPath(newCommitDirectoryPath, diffInfo.first));
    }

    output.flush();

    output.close();
}

bool OperationAccumulator::commit(const string& commitMessage, const bool addFlag) {  
  vector<string> verifiedAddedFiles;
  
  if (addFlag) {
    // Make sure that files that were added haven't been deleted in the time since they've
    // been added
    for (const string& addedFile : addedFiles) {
      if (FileSystemInterface::fileExists(addedFile.c_str())) {
	verifiedAddedFiles.push_back(addedFile);
      }
    }
  }

  // Now found out which file have been deleted, and gets the diffs for the files that have
  // been changed
  vector<string> removedFiles;
  vector<pair<string, FileDiff> > diffs;
  calculateRemovalsAndDiffs(removedFiles, diffs);

  if (verifiedAddedFiles.size() == 0 && removedFiles.size() == 0 && diffs.size() == 0) {
    return false;
  }

  // We're going to output this info now
  writeOutCommit(commitMessage, verifiedAddedFiles, removedFiles, diffs);

  // Update internal state
  if (addFlag) {
    for (string addedFile : verifiedAddedFiles) {
      trackedFiles.push_back(addedFile);
    }
    addedFiles.clear();
  }

  initialCommitPerformed = true;
  
  return true;
}
