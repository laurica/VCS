#ifndef TREENODE
#define TREENODE

#include <string>
#include <vector>

// TreeNode class representing a branch
// It carries no information, except for the name of the new branch
class TreeNode {
 protected:
  std::string branch;
  size_t numChildren; // Required in reading and assembling the tree
  std::vector<TreeNode*> children;
 public:
  TreeNode(std::string branch);
  TreeNode(std::string branch, size_t numChildren);
  virtual ~TreeNode();
  void registerChild(TreeNode * child);
  virtual std::string toString() const;
  std::vector<TreeNode*> getChildren() const;
  static TreeNode * createTreeNodeFromString(const std::string& nodeString);
  std::string getBranch() const;
  virtual std::string getCommitString() const;
  size_t getNumChildren();
};

#endif
