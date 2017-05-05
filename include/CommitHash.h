#ifndef COMMITHASH
#define COMMITHASH

#include <string>

class CommitHash {
 private:
  static unsigned int curCommitCounter;
  const int myHash;

 public:
  CommitHash();
  explicit CommitHash(const std::string& hash);
  std::string toString() const;
  static CommitHash getLatestGeneratedHash();
  static void setSeed(const std::string& lastHash);
  static std::string getNullHash();
};

#endif
