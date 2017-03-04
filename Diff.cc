#include <iostream>

#include "Diff.h"

using namespace std;

Diff::Diff(vector<DiffElement> insertions, vector<DiffElement> deletions) :
  insertions(insertions), deletions(deletions) {}

void Diff::print() {
  cout << "Insertions size: " << insertions.size() << endl;
  for (vector<DiffElement>::iterator it = insertions.begin(); it != insertions.end();
       ++it) {
    it->print();
    cout << endl;
  }

  cout << "Deletions size: " << deletions.size() << endl;
  for (vector<DiffElement>::iterator it = deletions.begin(); it != deletions.end(); ++it) {
    it->print();
    cout << endl;
  }
}
