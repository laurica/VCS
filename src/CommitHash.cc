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
  if (hash == "") {
    myHash = -1;
  } else {
    myHash = stoi(hash);
  }
}

CommitHash CommitHash::getLatestGeneratedHash() {
  return CommitHash(to_string(curCommitCounter - 1));
}

void CommitHash::setSeed(const string& lastHash) {
  curCommitCounter = stoi(lastHash) + 1;
}
