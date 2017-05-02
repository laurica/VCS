#include <assert.h>
#include <queue>

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

bool Tree::initializeTree(const vector<string>& lines) {
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
  }

  return true;
}
