#ifndef OPERATIONACCUMULATOR
#define OPERATIONACCUMULATOR

#include <map>
#include <string>
#include <vector>

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
  bool fileAdded;
  std::vector<std::string> trackedFiles;

  void outputTrackedFiles() const;
  bool outputBasicInfo() const;
  bool alreadyTracked(const std::string& fileName) const;
  
public:
  OperationAccumulator();
  bool addFile(const std::string& fileName);
  void initializeProject(const std::string& projectName);
  void saveState() const;
  bool initialize();
};

#endif
