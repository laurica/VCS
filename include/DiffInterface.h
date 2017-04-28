#ifndef DIFFINTERFACE
#define DIFFINTERFACE

#include "FileDiff.h"

class DiffInterface {
 public:
  static FileDiff calculateFileDiff(
      const char * previousCommitFileName, const char * fileName);
};

#endif
