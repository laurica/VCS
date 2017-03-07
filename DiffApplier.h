#ifndef DIFFAPPLIER
#define DIFFAPPLIER

#include "Diff.h"

#include <vector>

class DiffApplier {
 public:
  static void applyDiff(const std::vector<Line>& originalFile, const Diff& diff,
			std::vector<Line>& newFile);
};

#endif
