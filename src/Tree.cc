#include <assert.h>

#include "Tree.h"

using namespace std;

Tree::Tree() : root(NULL), curNode(NULL) {}

void Tree::initialize(const string& firstBranch) {
    root = new TreeNode(firstBranch);
    curNode = root;
}

void Tree::registerNewBranch(const string& newBranch) {
    TreeNode * newBranchNode = new TreeNode(newBranch);
    curNode->registerChild(newBranchNode);
    curNode = newBranchNode;
}
