#ifndef TREE
#define TREE

#include <string>
#include <vector>

#include "CommitHash.h"
#include "TreeNode.h"

class Tree {
  TreeNode * root;
  TreeNode * curNode;

  bool determineCurrentNode(const std::string& branch,
			    const std::string& commit);
  
public:
  Tree();
  void initialize(const std::string& firstBranch);
  void registerNewBranch(const std::string& newBranch);
  void addCommit(const CommitHash& commit);
  void getPrintableTree(std::vector<std::string>& lines) const;
  bool initializeTree(const std::vector<std::string>& lines,
		      const std::string& branch, const std::string& commit);
  ~Tree();
};

#endif
