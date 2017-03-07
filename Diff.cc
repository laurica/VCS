#include <iostream>

#include "Diff.h"

using namespace std;

Diff::Diff(const vector<DiffElement> insertions, const vector<DiffElement> deletions) :
  insertions(insertions), deletions(deletions) {}

void Diff::print() const {
  cout << "Insertions size: " << insertions.size() << endl;
  for (vector<DiffElement>::const_iterator it = insertions.begin(); it != insertions.end();
       ++it) {
    it->print();
    cout << endl;
  }

  cout << "Deletions size: " << deletions.size() << endl;
  for (vector<DiffElement>::const_iterator it = deletions.begin(); it != deletions.end();
       ++it) {
    it->print();
    cout << endl;
  }
}

const std::vector<DiffElement>& Diff::getDeletions() const {
  return deletions;
}

const std::vector<DiffElement>& Diff::getInsertions() const {
  return insertions;
}
