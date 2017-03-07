#include "DiffApplier.h"

using namespace std;

void DiffApplier::applyDiff(const vector<Line>& originalFile, const Diff& diff,
			    vector<Line>& newFile) {
  // copy everything from originalFile to newFile
  for (vector<Line>::const_iterator it = originalFile.begin(); it != originalFile.end();
       ++it) {
    newFile.push_back(*it);
  }
  
  // delete everything with the given index
  const vector<DiffElement>& deletions = diff.getDeletions();

  for (vector<DiffElement>::const_reverse_iterator rit = deletions.rbegin();
       rit != deletions.rend(); ++rit) {
    // for each element, remove from original file at the index specified
    int idx = rit->getStartingLine();
    int numLines = rit->getNumLines();

    for (int i = 0; i < numLines; ++i) {
      newFile.erase(newFile.begin() + idx);
    }
  }

  // Figure out the indices! (They're different after the deletions!)
  vector<int> indexesToInsertAt;
  const vector<DiffElement>& insertions = diff.getInsertions();
  int currentIndex = 0;
  
  for (vector<DiffElement>::const_iterator it = insertions.begin(); it != insertions.end();
       ++it) {
    while (originalFile[currentIndex].getNumber() <= it->getStartingLine()) {
      ++currentIndex;
    }

    indexesToInsertAt.push_back(currentIndex);
  }

  int originalSize = originalFile.size();

  vector<DiffElement>::const_reverse_iterator rit = insertions.rbegin();
  
  for (vector<int>::reverse_iterator it = indexesToInsertAt.rbegin();
       it != indexesToInsertAt.rend(); ++it) {
      DiffElement currDiffElement = *rit;
      const vector<string>& newLines = currDiffElement.getLines();
    
    if (*it >= originalSize) {
      // push backs
      for (vector<string>::const_iterator lineIt = newLines.begin();
	   lineIt != newLines.end(); ++lineIt) {
	newFile.push_back(Line(0, *lineIt));
      }
      ++rit;
    } else {
      for (vector<string>::const_reverse_iterator lineIt = newLines.rbegin();
	   lineIt != newLines.rend(); ++lineIt) {
	newFile.insert(newFile.begin() + *it, Line(0, *lineIt));
      }
    }
  } // end for loop
}
