#include <sstream>

#include "CommitNode.h"
#include "TreeNode.h"

using namespace std;

TreeNode::TreeNode(string branch) : branch(branch), numChildren(0) {}

TreeNode::TreeNode(string branch, size_t numChildren) :
  branch(branch), numChildren(numChildren) {}

TreeNode::~TreeNode() {
  for (TreeNode * t : children) {
    delete t;
  }
}

void TreeNode::registerChild(TreeNode * newChild) {
    children.push_back(newChild);
    ++numChildren;
}

string TreeNode::toString() const {
  return "B " + branch + " " + to_string(children.size());
}

vector<TreeNode*> TreeNode::getChildren() const {
  return children;
}

TreeNode * TreeNode::createTreeNodeFromString(const string& nodeString) {
  istringstream iss(nodeString);

  string token;
  if (!(iss >> token)) {
    return NULL;
  }

  if (token != "B" && token != "C") {
    return NULL;
  }

  string secondToken;
  if (!(iss >> secondToken)) {
    return NULL;
  }

  const string branch = secondToken;
  string commitHash = "";
  
  if (token == "C") {
    // read in the hash
    if (!(iss >> secondToken)) {
      return NULL;
    }

    commitHash = secondToken;
  }

  if (!(iss >> secondToken)) {
    return NULL;
  }

  const int numChildren = stoi(secondToken);

  if (token == "B") {
    return new TreeNode(branch, numChildren);
  }

  return new CommitNode(branch, commitHash, numChildren);
}

size_t TreeNode::getNumChildren() {
  if (children.empty()) {
    return numChildren;
  }

  return children.size();
}
