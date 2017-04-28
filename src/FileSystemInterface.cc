#include <iostream>

#include <sys/stat.h>

#include "FileSystemInterface.h"

using namespace std;

bool FileSystemInterface::fileExists(const char * fileName) {
  struct stat info;

  return (stat(fileName, &info) == 0);
}

const int FileSystemInterface::createDirectory(const char * dirName) {
  if (fileExists(dirName)) {
    return 0;
  }
  
  return mkdir(dirName, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}

const string FileSystemInterface::appendPath(const string& firstPart,
					     const string& secondPart) {
    if (firstPart.length() == 0) {
        return secondPart;
    }
  
    if (firstPart.at(firstPart.length() - 1) == '/') {
        return firstPart + secondPart;
    }
    return firstPart + "/" + secondPart;
}

void FileSystemInterface::parseDirectoryStructure(
    const string& fileName, vector<string>& directories) {
    unsigned int offset = 0;
    
    while (true) {
      size_t locationOfSlash = fileName.find("/", offset);
      if (locationOfSlash == std::string::npos) {
	break;
      }

      directories.push_back(fileName.substr(0, locationOfSlash));
      offset = locationOfSlash + 1;
    }
}

void FileSystemInterface::createDirectories(
    const string& pathToDirectories, const vector<string> directories) {
  for (const string& directory : directories) {
    string completePath = appendPath(pathToDirectories, directory);
    createDirectory(completePath.c_str());
  }
}
