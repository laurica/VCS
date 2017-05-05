#ifndef COMMITNODE
#define COMMITNODE

#include <string>

#include "CommitHash.h"
#include "TreeNode.h"

class CommitNode : public TreeNode {
  const CommitHash hash;
 public:
  CommitNode(const std::string& branch, const CommitHash& hash);
  CommitNode(const std::string& branch,
	     const std::string& hash,
	     const size_t numChildren);
  virtual std::string toString() const override;
  virtual std::string getCommitString() const override;
};

#endif
