#ifndef COMMITNODE
#define COMMITNODE

#include <string>

#include "CommitHash.h"
#include "TreeNode.h"

class CommitNode : public TreeNode {
    const CommitHash& hash;
 public:
    CommitNode(const std::string& branch, const CommitHash& hash);
};

#endif
