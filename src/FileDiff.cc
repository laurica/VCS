#include <fstream>

#include "FileDiff.h"

using namespace std;

FileDiff::FileDiff(const vector<DiffElement> insertions, const vector<DiffElement> deletions) :
  insertions(insertions), deletions(deletions) {}

void FileDiff::print(const string& path) const {
  ofstream os;
  os.open(path);
  
  os << "insertions [" << insertions.size() << "]" << "\n";
  for (const DiffElement& insertion : insertions) {
    insertion.print(os);
    os << "\n";
  }

  os << "deletions [" << deletions.size() << "]" << "\n";
  for (const DiffElement& deletion : deletions) {
    deletion.print(os);
    os << "\n";
  }

  os << flush;
  os.close();
}

const std::vector<DiffElement>& FileDiff::getDeletions() const {
  return deletions;
}

const std::vector<DiffElement>& FileDiff::getInsertions() const {
  return insertions;
}

bool FileDiff::isEmptyDiff() const {
  return insertions.size() == 0 && deletions.size() == 0;
}
