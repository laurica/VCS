#include "CommitHash.h"

using namespace std;

unsigned int CommitHash::curCommitCounter = 0;

CommitHash::CommitHash() : myHash(curCommitCounter) {
  ++curCommitCounter;
}

CommitHash::CommitHash(const string& hash) :
  myHash(hash == "" ? -1 : stoi(hash)) {}

string CommitHash::toString() const {
  return to_string(myHash);
}

CommitHash CommitHash::getLatestGeneratedHash() {
  return CommitHash(to_string(curCommitCounter - 1));
}

void CommitHash::setSeed(const string& lastHash) {
  curCommitCounter = stoi(lastHash) + 1;
}

string CommitHash::getNullHash() {
  return to_string(-1);
}
