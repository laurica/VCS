#ifndef DIFFAPPLIER
#define DIFFAPPLIER

#include "FileDiff.h"

#include <queue>
#include <vector>

class DiffApplier {
 public:
  static void applyDiff(const std::vector<Line>& originalFile,
			const FileDiff& diff, std::vector<Line>& newFile);
  // Base file gives the original file, and acts as an output parameter
  // containing the final result
  static void applyManyDiffs(std::vector<Line>& baseFile, const FileDiff& diff1,
			     const FileDiff& diff2);
  static void applyManyDiffs(std::vector<Line>& baseFile,
			     std::queue<FileDiff>& diffsToApply);
};

#endif
