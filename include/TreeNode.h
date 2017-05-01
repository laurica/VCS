#ifndef TREENODE
#define TREENODE

#include <string>
#include <vector>

// TreeNode class representing a branch
// It carries no information, except for the name of the new branch
class TreeNode {
 protected:
    std::string branch;
    std::vector<TreeNode*> children;
    bool branchNode;
 public:
    TreeNode(std::string branch);
    void registerChild(TreeNode * child);
};

#endif
