#ifndef OPERATIONACCUMULATOR
#define OPERATIONACCUMULATOR

#include <string>
#include <vector>

class OperationAccumulator {
  bool projectInit;
  bool projectInitializedThisRun;
  std::string projectName;
  std::vector<std::string> trackedFiles;
  std::vector<std::string> filesToAdd;

  void outputTrackedFiles() const;
  bool outputBasicInfo() const;
  
public:
  OperationAccumulator();
  void addFile(const std::string& fileName);
  void projectInitialized(const std::string& projectName);
  void saveState() const;
};

#endif
