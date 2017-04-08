#include <fstream>
#include <iostream>

#include "FileParser.h"
#include "FileSystemInterface.h"
#include "OperationAccumulator.h"

using namespace std;

OperationAccumulator::OperationAccumulator() :
  projectInit(false), projectInitializedThisRun(false) {
  fileNames[FileName::MAIN_DIR] = ".kil";
  fileNames[FileName::BASIC_INFO] = ".kil/.basicInfo.txt";
  fileNames[FileName::TRACKED_FILES] = ".kil/.trackedFiles.txt";
}

void OperationAccumulator::initializeProject(const std::string& fileName) {
  projectInit = true;
  projectInitializedThisRun = true;
  projectName = fileName;
}

bool OperationAccumulator::alreadyTracked(const string& fileName) const {
  for (string file : trackedFiles) {
    if (fileName == file) {
      return true;
    }
  }

  return false;
}

void OperationAccumulator::addFile(const string& fileName) {
  // Do we already have this file
  if (!alreadyTracked(fileName)) {
    trackedFiles.push_back(fileName);
  }
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

  outputStream << flush;
  outputStream.close();

  return true;
}

bool OperationAccumulator::initialize() {
  // try and see if the .kil directory is created
  if (!(FileSystemInterface::fileExists(fileNames.at(FileName::MAIN_DIR)))) {
    return false;
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

  if (lines.size() != 1) {
    cout << error << endl;
    return false;
  }

  if (lines[0].find("projName=") != 0) {
    cout << error << endl;
    return false;
  }

  if (lines[0].substr(lines[0].find("projName=") + 8).length() == 0) {
    cout << error << endl;
  }

  projectName = lines[0].substr(lines[0].find("projName=") + 8);

  // read in from the trackedFiles file
  lines.clear();
  FileParser::readFile(fileNames.at(FileName::TRACKED_FILES), lines);
  for (string fileName : lines) {
    trackedFiles.push_back(fileName);
  }

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
  
  outputTrackedFiles();
}
