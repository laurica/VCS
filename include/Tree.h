#ifndef TREE
#define TREE

#include <string>
#include <vector>

#include "TreeNode.h"

class Tree {
  TreeNode * root;
  TreeNode * curNode;
    
public:
  Tree();
  void initialize(const std::string& firstBranch);
  void registerNewBranch(const std::string& newBranch);
  void getPrintableTree(std::vector<std::string>& lines) const;
  bool initializeTree(const std::vector<std::string>& lines);
  ~Tree();
};

#endif
