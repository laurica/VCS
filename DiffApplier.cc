#include "DiffApplier.h"

using namespace std;

static void reindex(vector<Line>& file) {
  unsigned int curElem = 0;

  for (vector<Line>::iterator it = file.begin(); it != file.end(); ++it) {
    it->setLineNumber(curElem);
    ++curElem;
  }
}

void DiffApplier::applyDiff(const vector<Line>& originalFile, const Diff& diff,
			    vector<Line>& newFile) {
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

void DiffApplier::applyManyDiffs(std::vector<Line>& baseFile, const Diff& diff1,
				 const Diff& diff2) {
  vector<Line> newFile;
  DiffApplier::applyDiff(baseFile, diff1, newFile);
  reindex(newFile);
  baseFile = newFile;
  newFile.clear();
  DiffApplier::applyDiff(baseFile, diff2, newFile);
  baseFile = newFile;
}

void DiffApplier::applyManyDiffs(std::vector<Line>& baseFile,
				 std::queue<Diff>& diffsToApply) {
  while (!diffsToApply.empty()) {
    vector<Line> newFile;
    Diff d = diffsToApply.front();
    diffsToApply.pop();
    DiffApplier::applyDiff(baseFile, d, newFile);
    reindex(newFile);
    baseFile = newFile;
  }
}

// TODO: Handle the case of inserted a line that was formerly deleted
void DiffApplier::mergeDiffs(Diff& diff1, const Diff& diff2) {
  // first we look at all of the insertions we make in diff2
  vector<DiffElement> insertions2 = diff2.getInsertions();
  vector<DiffElement> insertions1 = diff1.getInsertions();
  
  vector<DiffElement>::iterator insertions1It = insertions1.begin();
  
  for (vector<DiffElement>::const_iterator insertions2It = insertions2.begin();
       insertions2It != insertions2.end(); ++insertions2It) {
    // iterate through the other insertions until we find one we're inserting in
    // the middle of, or until we pass by the last compatible insertion
    while (insertions1It != insertions1.end() &&
	   insertions1It->getNewStartingLine() <=
	   insertions2It->getBaseStartingLine()) {
      ++insertions1It;
    }

    if (insertions1It == insertions1.begin()) {
      // this element comes before any element of insertions1
      // we can insert this element at the start of insertions1
      insertions1.push_back(*insertions2It);
      // This also handles the case of insertions1 being empty!
    } else {
      --insertions1It;
      // Now insertions1 is pointing to the last element coming before
      // insertions2
      // Check if iterator2->getBaseStartingLine falls in
      // insertions1[start, end + 1]
      // the ending index is actually startingLine + numLines - 1, so when we
      // add a +1 to include the next index, the +1 and -1 cancel
      unsigned int endingIndex = insertions1It->getNewStartingLine() +
	insertions1It->getNumLines();
      if (insertions1It->getNewStartingLine() <=
	  insertions2It->getBaseStartingLine() &&
	  insertions2It->getBaseStartingLine() <= endingIndex) {
	// merge these two insertions
	insertions1It->
	  mergeInAdditionalChanges(insertions2It->getBaseStartingLine(),
				   insertions2It->getLines());
      } else {
	// create a new insertion diff element
	insertions1.insert(insertions1It,
			   (DiffElement(ElementType::INSERTION,
					insertions2It->getLines())));
      }
    }
  }

  // VERY IMPORTANT! Once all of the new changes have been applied, reindex the
  // lines! When the new diff elements are created, the lines they contain have
  // dummy data in the line number field.
}
