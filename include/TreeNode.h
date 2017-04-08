#ifndef TREENODE
#define TREENODE

#include <string>
#include <vector>

class TreeNode {
  int ID;
  std::string commitMessage;
  // Also include a diff!
  std::vector<TreeNode> children;
};

#endif
