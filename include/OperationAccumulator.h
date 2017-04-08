#ifndef OPERATIONACCUMULATOR
#define OPERATIONACCUMULATOR

#include <map>
#include <string>
#include <vector>

#include "Tree.h"

class OperationAccumulator {
  enum FileName {
    MAIN_DIR,
    BASIC_INFO,
    TRACKED_FILES
  };

  std::map<FileName, const char *> fileNames;
  
  bool projectInit;
  bool projectInitializedThisRun;
  std::string projectName;

  bool listOfFilesRead;
  bool fileAdded;
  std::vector<std::string> trackedFiles;
  std::vector<std::string> addedFiles;
  
  bool branchChanged;
  std::string curBranch;
  
  bool treeInitialized;
  Tree tree;
  
  void outputTrackedFiles() const;
  bool outputBasicInfo() const;
  bool alreadyTracked(const std::string& fileName) const;
  void createDiff() const;
  
public:
  OperationAccumulator();
  bool addFile(const std::string& fileName);
  void initializeProject(const std::string& projectName);
  void saveState() const;
  bool initialize();
  bool isInitialized() const;
  std::string getCurBranchName() const;
  void commit();
};

#endif
