#ifndef OPERATIONACCUMULATOR
#define OPERATIONACCUMULATOR

#include <fstream>
#include <map>
#include <string>
#include <vector>

#include "CommitHash.h"
#include "FileDiff.h"
#include "Tree.h"

class OperationAccumulator {
  enum FileName {
    MAIN_DIR,
    BASIC_INFO,
    ADDED_FILES,
    TRACKED_FILES,
    COMMIT_DIR
  };

  std::map<FileName, const char *> fileNames;
  
  bool projectInit;
  std::string projectName;

  std::vector<std::string> trackedFiles;
  std::vector<std::string> addedFiles;
  
  std::string curBranch;

  bool initialCommitPerformed;
  CommitHash curCommit;

  Tree tree;
  
  void outputTrackedFiles() const;
  void outputAddedFiles() const;
  bool outputBasicInfo() const;
  bool alreadyTracked(const std::string& fileName) const;
  void createDiff() const;
  bool readAddedAndTrackedFiles(const std::string& errorMessage);
  void createNewCommitDirectory(const std::string& newCommitDirectoryPath) const;
  void updateParentCommit(const CommitHash& childHash) const;
  std::string calculateFileLocationForHash(const CommitHash& hash) const;
  void writeBasicCommitInfo(std::ofstream& output, const std::string& newCommitFileName,
			    const CommitHash& hash, const std::string& commitMessage) const;
  void removeDeletedFilesFromLists(const std::vector<std::string>& removedFiles);
  void writeOutAddedFiles(std::ofstream& output,
			  const std::vector<std::string>& addedFiles,
			  const std::string& newCommitDirectoryPath) const;
  void getAddedFiles(std::vector<std::string>& verifiedAddedFiles) const;
  
public:
  OperationAccumulator();
  bool addFile(const std::string& fileName);
  void initializeProject(const std::string& projectName);
  void saveState() const;
  bool initialize();
  bool isInitialized() const;
  std::string getCurBranchName() const;
  void calculateRemovalsAndDiffs(
      std::vector<std::string>& removedFiles,
      std::vector<std::pair<std::string, FileDiff> >& diffs) const;
  bool commit(const std::string& commitMessage, const bool addFlag);
  void writeOutCommit(
      const std::string& commitMessage, const std::vector<std::string>& addedFiles,
      const std::vector<std::string>& removedFiles,
      const std::vector<std::pair<std::string, FileDiff> >& diffs);
  void getStatus() const;
  void createNewBranch(const std::string& newBranchName);
};

#endif
