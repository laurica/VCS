#//include <boost/filesystem.hpp>

#include <fstream>
#include <iostream>

#include "OperationAccumulator.h"

using namespace std;

OperationAccumulator::OperationAccumulator() :
  projectInit(false), projectInitializedThisRun(false) {}

void OperationAccumulator::projectInitialized(const std::string& fileName) {
  projectInit = true;
  projectInitializedThisRun = true;
  projectName = fileName;
}

void OperationAccumulator::addFile(const string& fileName) {
  filesToAdd.push_back(fileName);
}

void OperationAccumulator::outputTrackedFiles() const {
  string trackedFileConfigFileName = ".kil/.trackedFiles.txt";

  ofstream outputStream;
  outputStream.open(trackedFileConfigFileName, fstream::out);
  
  for (string trackedFile : trackedFiles) {
    outputStream << trackedFile << "\n";
  }

  for (string newTrackedFile : filesToAdd) {
    outputStream << newTrackedFile << endl;
  }

  outputStream << flush;
  outputStream.close();
}

bool OperationAccumulator::outputBasicInfo() const {
  /*boost::filesystem::path dir("./.kil");
  if(!boost::filesystem::create_directory(dir)) {
    cout << "Could not initialize project!" << "\n";
    return false;
    }*/
  
  string basicProjectInfoFileName = ".kil/.basicInfo.txt";
  
  ofstream outputStream;
  outputStream.open(basicProjectInfoFileName, fstream::out);

  outputStream << "projName=" << projectName << "\n";

  outputStream << flush;
  outputStream.close();

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
