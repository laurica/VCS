#include "CommitNode.h"

using namespace std;

CommitNode::CommitNode(const string& branch, const CommitHash& hash) :
    TreeNode(branch), hash(hash) {
    branchNode = false;
}
