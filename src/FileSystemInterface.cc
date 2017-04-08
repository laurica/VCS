#include <sys/stat.h>

#include "FileSystemInterface.h"

bool FileSystemInterface::fileExists(const char * fileName) {
  struct stat info;

  return (stat(fileName, &info) == 0);
}

const int FileSystemInterface::createDirectory(const char * dirName) {
  return mkdir(dirName, S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
}
