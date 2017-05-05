#include "CommitNode.h"

using namespace std;

CommitNode::CommitNode(const string& branch, const CommitHash& hash) :
  TreeNode(branch), hash(hash) {}

CommitNode::CommitNode(const string& branch, const string& hash,
		       const size_t numChildren) :
  TreeNode(branch, numChildren), hash(CommitHash(hash)) {}

string CommitNode::toString() const {
  return "C " + branch + " " + hash.toString() + " " +
    to_string(children.size());
}

string CommitNode::getCommitString() const {
  return hash.toString();
}
