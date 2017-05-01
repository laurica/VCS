#ifndef TREE
#define TREE

#include <string>

#include "TreeNode.h"

class Tree {
    TreeNode * root;
    TreeNode * curNode;
    
 public:
    Tree();
    void initialize(const std::string& firstBranch);
    void registerNewBranch(const std::string& newBranch);
    // TODO:
    // WRITE DESTRUCTOR
    //~Tree();
};

#endif
