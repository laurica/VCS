#include "TreeNode.h"

using namespace std;

TreeNode::TreeNode(string branch) : branch(branch), branchNode(true) {}

void TreeNode::registerChild(TreeNode * newChild) {
    children.push_back(newChild);
}
