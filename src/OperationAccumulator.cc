#include <fstream>
#include <iostream>

#include "FileParser.h"
#include "FileSystemInterface.h"
#include "OperationAccumulator.h"

using namespace std;

OperationAccumulator::OperationAccumulator() :
  projectInit(false), projectInitializedThisRun(false), fileAdded(false),
  branchChanged(false) {
  fileNames[FileName::MAIN_DIR] = ".kil";
  fileNames[FileName::BASIC_INFO] = ".kil/.basicInfo.txt";
  fileNames[FileName::TRACKED_FILES] = ".kil/.trackedFiles.txt";
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

  return false;
}

bool OperationAccumulator::addFile(const string& fileName) {
  vector<string> lines;
  // read in from the trackedFiles file
  FileParser::readFile(fileNames.at(FileName::TRACKED_FILES), lines);
  for (string fileName : lines) {
    trackedFiles.push_back(fileName);
  }
  
  // Do we already have this file
  if (!alreadyTracked(fileName)) {
    trackedFiles.push_back(fileName);
    fileAdded = true;
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

bool OperationAccumulator::outputBasicInfo() const {
  string path = "./.kil";
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
  
  outputStream << flush;
  outputStream.close();

  return true;
}

bool OperationAccumulator::initialize() {
  // try and see if the .kil directory is created
  if (!(FileSystemInterface::fileExists(fileNames.at(FileName::MAIN_DIR)))) {
    return true;
  }

  projectInit = true;

  string error = "Error! KIL information tampered with or missing!";
  
  // make sure that all of the information that needs to be there, is there
  if (!(FileSystemInterface::fileExists(fileNames.at(FileName::BASIC_INFO)))) {
    cout << error << endl;
    return false;
  }

  vector<string> lines;
  FileParser::readFile(fileNames.at(FileName::BASIC_INFO), lines);

  if (lines.size() != 2) {
    cout << error << endl;
    return false;
  }

  if (lines[0].find("projName=") != 0) {
    cout << error << endl;
    return false;
  }

  if (lines[0].substr(9).length() == 0) {
    cout << error << endl;
  }

  if (lines[1].find("curBranch=") != 0) {
    cout << error << endl;
    return false;
  }

  if (lines[1].substr(10).length() == 0) {
    cout << error << endl;
    return false;
  }

  projectName = lines[0].substr(9);
  curBranch = lines[1].substr(10);
  
  return true;
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

  if (fileAdded) {
    outputTrackedFiles();
  }
}

bool OperationAccumulator::isInitialized() const {
  return projectInit;
}

string OperationAccumulator::getCurBranchName() const {
  return curBranch;
}
