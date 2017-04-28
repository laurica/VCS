#ifndef FILESYSTEMINTERFACE
#define FILESYSTEMINTERFACE

#include <string>
#include <vector>

class FileSystemInterface {
public:
  static bool fileExists(const char * fileName);
  static const int createDirectory(const char * dirName);
  static const std::string appendPath(
      const std::string& firstPart, const std::string& secondPart);
  static void parseDirectoryStructure(
      const std::string& fileName, std::vector<std::string>& directories);
  static void createDirectories(
      const std::string& pathToDirectories, const std::vector<std::string> directories);
};

#endif
