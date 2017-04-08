#include "DiffApplier.h"

using namespace std;

static void reindex(vector<Line>& file) {
  unsigned int curElem = 0;

  for (vector<Line>::iterator it = file.begin(); it != file.end(); ++it) {
    it->setLineNumber(curElem);
    ++curElem;
  }
}

void DiffApplier::applyDiff(const vector<Line>& originalFile,
			    const FileDiff& diff, vector<Line>& newFile) {
  /*************** copy everything from originalFile to newFile ***************/
  for (vector<Line>::const_iterator it = originalFile.begin();
       it != originalFile.end(); ++it) {
    newFile.push_back(*it);
  }
  
  /****************** delete everything with the given index ******************/
  const vector<DiffElement>& deletions = diff.getDeletions();

  for (vector<DiffElement>::const_reverse_iterator rit = deletions.rbegin();
       rit != deletions.rend(); ++rit) {
    // for each element, remove from original file at the index specified
    int idx = rit->getBaseStartingLine();
    int numLines = rit->getNumLines();

    for (int i = 0; i < numLines; ++i) {
      newFile.erase(newFile.begin() + idx);
    }
  }

  // At this point newFile contains the longest common subsequence!

  /** Figure out the indices in the newFile vector we need to insert the new **/
  /** lines at                                                               **/
  vector<int> indicesToInsertAt;
  const vector<DiffElement>& insertions = diff.getInsertions();
  int currentIndex = 0;
  
  for (vector<DiffElement>::const_iterator it = insertions.begin();
       it != insertions.end(); ++it) {
    while (newFile[currentIndex].getNumber() < it->getBaseStartingLine()) {
      ++currentIndex;
    }

    indicesToInsertAt.push_back(currentIndex );
    ++currentIndex;
  }
  
  int originalSize = originalFile.size();

  vector<DiffElement>::const_reverse_iterator rit = insertions.rbegin();
  
  for (vector<int>::reverse_iterator it = indicesToInsertAt.rbegin();
       it != indicesToInsertAt.rend(); ++it) {
    DiffElement currDiffElement = *rit;
    const vector<string>& newLines = currDiffElement.getLines();
    
    if (*it >= originalSize) {
      // push backs
      for (vector<string>::const_iterator lineIt = newLines.begin();
	   lineIt != newLines.end(); ++lineIt) {
	newFile.push_back(Line(0, *lineIt));
      }
    } else {
      for (vector<string>::const_reverse_iterator lineIt = newLines.rbegin();
	   lineIt != newLines.rend(); ++lineIt) {
	newFile.insert(newFile.begin() + *it, Line(0, *lineIt));
      }
    }

    ++rit;
  } // end for loop
}

void DiffApplier::applyManyDiffs(std::vector<Line>& baseFile,
				 const FileDiff& diff1, const FileDiff& diff2) {
  vector<Line> newFile;
  DiffApplier::applyDiff(baseFile, diff1, newFile);
  reindex(newFile);
  baseFile = newFile;
  newFile.clear();
  DiffApplier::applyDiff(baseFile, diff2, newFile);
  baseFile = newFile;
}

void DiffApplier::applyManyDiffs(std::vector<Line>& baseFile,
				 std::queue<FileDiff>& diffsToApply) {
  while (!diffsToApply.empty()) {
    vector<Line> newFile;
    FileDiff d = diffsToApply.front();
    diffsToApply.pop();
    DiffApplier::applyDiff(baseFile, d, newFile);
    reindex(newFile);
    baseFile = newFile;
  }
}
