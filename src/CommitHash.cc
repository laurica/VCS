#include "CommitHash.h"

using namespace std;

unsigned int CommitHash::curCommitCounter = 0;

CommitHash::CommitHash() {
  myHash = curCommitCounter;
  ++curCommitCounter;
}

string CommitHash::toString() const {
  return to_string(myHash);
}

CommitHash::CommitHash(const string& hash) {
  unsigned int hashNumber = stoi(hash);
  myHash = hashNumber;
}