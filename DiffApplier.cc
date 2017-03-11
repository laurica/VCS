#include "DiffApplier.h"

using namespace std;

void DiffApplier::applyDiff(const vector<Line>& originalFile, const Diff& diff,
			    vector<Line>& newFile) {
  /******************** copy everything from originalFile to newFile ********************/
  for (vector<Line>::const_iterator it = originalFile.begin(); it != originalFile.end();
       ++it) {
    newFile.push_back(*it);
  }
  
  /******************** delete everything with the given index ********************/
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

  /******************** Figure out the indices in the newFile vector we need to insert the new ********************/
  /******************** lines at                                                               ********************/
  vector<int> indicesToInsertAt;
  const vector<DiffElement>& insertions = diff.getInsertions();
  int currentIndex = 0;
  
  for (vector<DiffElement>::const_iterator it = insertions.begin(); it != insertions.end();
       ++it) {
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

static void reindex(vector<Line>& file) {
  unsigned int curElem = 0;

  for (vector<Line>::iterator it = file.begin(); it != file.end(); ++it) {
    it->setLineNumber(curElem);
    ++curElem;
  }
}

void DiffApplier::applyManyDiffs(std::vector<Line>& baseFile, const Diff& diff1, const Diff& diff2) {
  vector<Line> newFile;
  DiffApplier::applyDiff(baseFile, diff1, newFile);
  reindex(newFile);
  baseFile = newFile;
  newFile.clear();
  DiffApplier::applyDiff(baseFile, diff2, newFile);
  baseFile = newFile;
}

void DiffApplier::applyManyDiffs(std::vector<Line>& baseFile, std::queue<Diff>& diffsToApply) {
  while (!diffsToApply.empty()) {
    vector<Line> newFile;
    Diff d = diffsToApply.front();
    diffsToApply.pop();
    DiffApplier::applyDiff(baseFile, d, newFile);
    reindex(newFile);
    baseFile = newFile;
  }
}

/*static void getOneSetOfIntersectingDiffElements(unsigned int startingIndex, unsigned int endingIndex,
						vector<DiffElement>& otherElements) {
  // Store the indices we want to delete at
  vector<int> indicesToDeleteAt;
  int ctr = 0;
  
  for (vector<DiffElement>::iterator it = otherElements.begin(); it != otherElements.end(); ++it) {
    unsigned int startOfCurElement = it->getStartingLine();
    unsigned int endOfCurElement = startOfCurElement + it->getNumLines() - 1;
    if (startOfCurElement <= endingIndex && endOfCurElement >= startingIndex) {
      indicesToDeleteAt.push_back(ctr);
    }
    
    ++ctr;
  }

  for (vector<int>::reverse_iterator it = indicesToDeleteAt.rbegin(); it != indicesToDeleteAt.rend(); ++it) {
    otherElements.erase(otherElements.begin() + *it);
  }
}

static void getIntersectingDiffElements(const DiffElement& e, vector<DiffElement>& intersectingInsertions,
					vector<DiffElement>& intersectingDeletions) {
  // get everything in the range [startingLine - 1] to [endingLine + 1]
  // the -1/+1 is to account for the fact that we want to condense ranges that border each other
  // eg. [2,5] and [6,10] should be condensed to [2,10]
  unsigned int startingIndex = (e.getStartingLine() == 0) ? 0 : e.getStartingLine() - 1;
  // Note that the endingLine is on index startingIndex + getNumLines() - 1, so our -1/+1 cancel
  unsigned int endingIndex = startingIndex + e.getNumLines();

  getOneSetOfIntersectingDiffElements(startingIndex, endingIndex, intersectingInsertions);
  getOneSetOfIntersectingDiffElements(startingIndex, endingIndex, intersectingDeletions);
}*/

/*void DiffApplier::mergeDiffs(const Diff& diff1, const Diff& diff2) {
  //diff1.print();
  //diff2.print();

  vector<DiffElement> insertions1 = diff1.getInsertions();
  vector<DiffElement> deletions1 = diff1.getDeletions();

  const vector<DiffElement>& insertions2 = diff2.getInsertions();
  const vector<DiffElement>& deletions2 = diff2.getDeletions();

  if (deletions2.size() == 0) {
  }

  vector<DiffElement>::const_iterator it = insertions1.begin();
  
  // for every element in insertions2, find everything it intersects with
  for (vector<DiffElement>::const_iterator it2 = insertions2.begin(); it2 != insertions2.end(); ++it2) {
    // check if the insertions co-incide with deletions
    //vector<DiffElement> intersectingInsertions = insertions1;
    //vector<DiffElement> intersectingDeletions = deletions1;
    // get the intersecting insertions, if any
    while (it->getStartingLine() < it2->getStartingLine()) {
      ++it;
    }


    //getIntersectingDiffElements(*it, intersectingInsertions, intersectingDeletions);
    // if they don't, it's easy, either merge them into an existing insertion, or create a new insertion
    // if it does co-incide with a deletion, 
  }
  }*/

/*void DiffApplier::mergeDiffs(const Diff& diff1, const Diff& diff2) {
  //diff1.print();
  //diff2.print();

  vector<DiffElement> insertions1 = diff1.getInsertions();
  vector<DiffElement> deletions1 = diff1.getDeletions();

  const vector<DiffElement>& insertions2 = diff2.getInsertions();
  const vector<DiffElement>& deletions2 = diff2.getDeletions();

  if (deletions2.size() == 0) {
  }

  vector<DiffElement>::const_iterator it = insertions1.begin();

  // TODO:
  // Check if some of the deletions of it match up with the insertions of it2
  // If they cancel, get rid of them
  //
  
  // for every element in insertions2, find everything it intersects with
  for (vector<DiffElement>::const_iterator it2 = insertions2.begin(); it2 != insertions2.end(); ++it2) {
    // We want to find the member of insertions1 whose first element comes just before *it2
    while (it->getStartingLine() <= it2->getStartingLine()) {
      ++it;
    }
    
    if (it == insertions1.begin()) {
      // this element comes before any element of 'it'
      // we can insert this element at the start of insertions1
      insertions1.push_back(*it2);
    } else {
      --it;
      // Now 'it' is pointing to the last element coming before it2
      // Check if it2->getStartingLine falls in it[start, end]
      if (it2->getStartingLine >= it->getStartingLine && it2->getStartingLine >= ) {
      } else {
      }
    }

    // if they don't, it's easy, either merge them into an existing insertion, or create a new insertion
    // if it does co-incide with a deletion, 
  }
  }*/
