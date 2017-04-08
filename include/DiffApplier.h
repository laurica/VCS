#ifndef DIFFAPPLIER
#define DIFFAPPLIER

#include "Diff.h"

#include <queue>
#include <vector>

class DiffApplier {
 public:
  static void applyDiff(const std::vector<Line>& originalFile, const Diff& diff,
			std::vector<Line>& newFile);
  // Base file gives the original file, and acts as an output parameter
  // containing the final result
  static void applyManyDiffs(std::vector<Line>& baseFile, const Diff& diff1,
			     const Diff& diff2);
  static void applyManyDiffs(std::vector<Line>& baseFile,
			     std::queue<Diff>& diffsToApply);
};

#endif
