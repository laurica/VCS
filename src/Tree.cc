#include <assert.h>
#include <iostream>
#include <queue>

#include "CommitNode.h"
#include "Tree.h"

using namespace std;

Tree::Tree() : root(NULL), curNode(NULL) {}

Tree::~Tree() {
  delete root;
}

void Tree::initialize(const string& firstBranch) {
  root = new TreeNode(firstBranch);
  curNode = root;
}

void Tree::registerNewBranch(const string& newBranch) {
  assert(curNode != NULL);
  TreeNode * newBranchNode = new TreeNode(newBranch);
  curNode->registerChild(newBranchNode);
  curNode = newBranchNode;
}

void Tree::addCommit(const CommitHash& commit) {
  assert(curNode != NULL);
  CommitNode * newCommitNode = new CommitNode(curNode->getBranch(), commit);
  curNode->registerChild(newCommitNode);
  curNode = newCommitNode;
}

void Tree::getPrintableTree(vector<string>& lines) const {
  // breadth first representation of a tree
  assert(root != NULL);

  queue<TreeNode*> nodesToProcess;
  nodesToProcess.push(root);

  while (!nodesToProcess.empty()) {
    // look at the node in the front, and push back all of its children
    TreeNode * node = nodesToProcess.front();

    for (TreeNode * childNode : node->getChildren()) {
      nodesToProcess.push(childNode);
    }
    
    lines.push_back(node->toString());
    nodesToProcess.pop();
  }
}

bool Tree::determineCurrentNode(const string& branch, const string& commit) {
  queue<TreeNode*> nodes;
  nodes.push(root);

  while (!nodes.empty()) {
    TreeNode * node = nodes.front();
    if (node->isNewBranchNode()) {
      if (node->getBranch() == branch) {
	curNode = node;
	return true;
      }
    } else if (node->getBranch() == branch &&
	       node->getCommitString() == commit) {
      curNode = node;
      return true;
    }

    for (TreeNode * childNode : node->getChildren()) {
      nodes.push(childNode);
    }

    nodes.pop();
  }

  return false;
}

bool Tree::initializeTree(const vector<string>& lines,
			  const string& branch, const string& commit) {
  queue<TreeNode*> processingNodeQueue;
  queue<TreeNode*> relationshipNodeQueue;
  
  // Read the info in into two queues
  for (const string& line : lines) {
    TreeNode * node = TreeNode::createTreeNodeFromString(line);
    if (node == NULL) {
      return false;
    }

    processingNodeQueue.push(node);
    relationshipNodeQueue.push(node);
  }

  relationshipNodeQueue.pop();

  root = processingNodeQueue.front();

  // Now, iterate through the processing queue
  // Get numChildren for that node
  // And take that many from the relationship queue to be its children
  while (!processingNodeQueue.empty()) {
    TreeNode * node = processingNodeQueue.front();

    size_t numChildren = node->getNumChildren();
    for (size_t i = 0; i < numChildren; ++i) {
      node->registerChild(relationshipNodeQueue.front());
      relationshipNodeQueue.pop();
    }

    processingNodeQueue.pop();
  }

  return determineCurrentNode(branch, commit);
}
