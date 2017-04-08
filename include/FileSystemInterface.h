#ifndef FILESYSTEMINTERFACE
#define FILESYSTEMINTERFACE

class FileSystemInterface {
public:
  static bool fileExists(const char * fileName);
  static const int createDirectory(const char * dirName);
};

#endif
