#include "SubsequenceAnalyzer.h"
#include <algorithm>
#include <iostream>
#include "DeletedLine.h"

using namespace std;

enum VectorToSelectFrom {
    SUBSEQUENCE,
    INSERTIONS,
    DELETIONS
};

static VectorToSelectFrom selectFirstFromThree(vector<Line>::iterator subIt,
                                               vector<NewLine>::iterator newIt,
                                               vector<DeletedLine>::iterator delIt) {
    if (subIt->getNumber() <= newIt->getNumber() && 
        subIt->getNumber() <= delIt->getNumber()) {
        return SUBSEQUENCE;
    }

    if (delIt->getNumber() <= newIt->getNumber()) {
        return DELETIONS;
    }

    return INSERTIONS;
}

static VectorToSelectFrom selectFirst(vector<Line>& subsequence,
				      vector<NewLine>& insertions,
				      vector<DeletedLine>& deletions,
				      vector<Line>::iterator subIt, 
				      vector<NewLine>::iterator newIt, 
				      vector<DeletedLine>::iterator delIt) {
  if (subIt != subsequence.end()) {
    if (newIt != insertions.end()) {
      if (delIt != deletions.end()) {
	// all three
	return selectFirstFromThree(subIt, newIt, delIt);
      }

      // subIt or newIt
      return (subIt->getNumber() <= newIt->getNumber()) ? SUBSEQUENCE : INSERTIONS;
    }

    if (delIt != deletions.end()) {
      return subIt->getNumber() <= delIt->getNumber() ? SUBSEQUENCE : DELETIONS;
    }

    return SUBSEQUENCE;
  } else {
    // insertions or deletions
    if (newIt != insertions.end()) {
      if (delIt != deletions.end()) {
	return delIt->getNumber() <= delIt->getNumber() ? DELETIONS : INSERTIONS;
      }

      return INSERTIONS;
    }

    return DELETIONS;
  }
}

template <class T>
static void takeAllConsecutive(vector<T>& sequence, typename vector<T>::iterator& it) {
  int curNum = it->getNumber();
  cout << it->getString() << endl;
  ++it;

  while (it != sequence.end() && it->getNumber() == curNum + 1) {
    ++curNum;
    cout << it->getString() << endl;
    ++it;
  }
}

static void outputDiff(vector<Line>& subsequence, vector<NewLine>& insertions,
		  vector<DeletedLine>& deletions) {
  
    // Take the vector currently at the lowest index
    // Print all the consecutive lines
    // If there are ever ties for lowest index, the priority is subsequence 
    // first, deletions second, and insertions third
    vector<Line>::iterator subIt = subsequence.begin();
    vector<NewLine>::iterator newIt = insertions.begin();
    vector<DeletedLine>::iterator delIt = deletions.begin();

    subIt = subsequence.begin();
    newIt = insertions.begin();
    delIt = deletions.begin();
    
    while (subIt != subsequence.end() || newIt != insertions.end()
           || delIt != deletions.end()) {
        VectorToSelectFrom v = selectFirst(subsequence, insertions, deletions,
					   subIt, newIt, delIt);
	switch (v) {
	case SUBSEQUENCE:
	  takeAllConsecutive<Line>(subsequence, subIt);
	  break;
	case DELETIONS:
	  takeAllConsecutive<DeletedLine>(deletions, delIt);
	  break;
	case INSERTIONS:
	  takeAllConsecutive<NewLine>(insertions, newIt);
	  break;
	}
	// continue taking as much as possible
    }
}

static void getInsertions(vector<Line>& subsequence, vector<Line>& newString,
			  vector<NewLine>& insertedLines) {
    vector<Line>::iterator newStringIt = newString.begin();
    vector<Line>::iterator subsequenceIt = subsequence.begin();

    // Everything contained in newString but not in subsequence is an inserted line
    while (subsequenceIt != subsequence.end()) {
        if ((*subsequenceIt).equals(*newStringIt)) {
            ++subsequenceIt;
            ++newStringIt;
        } else {
            insertedLines.push_back(NewLine(*newStringIt));
            ++newStringIt;
        }
    }

    while (newStringIt != newString.end()) {
        insertedLines.push_back(NewLine(*newStringIt));
        ++newStringIt;
    }
}

static void getDeletions(vector<Line>& subsequence, vector<Line>& oldString,
			 vector<DeletedLine>& deletedLines) {
    vector<Line>::iterator oldStringIt = oldString.begin();
    vector<Line>::iterator subsequenceIt = subsequence.begin();

    while (subsequenceIt != subsequence.end()) {
        if ((*subsequenceIt).equals(*oldStringIt)) {
            ++subsequenceIt;
            ++oldStringIt;
        } else {
            deletedLines.push_back(DeletedLine(*oldStringIt));
            ++oldStringIt;
        }
    }

    while (oldStringIt != oldString.end()) {
        deletedLines.push_back(DeletedLine(*oldStringIt));
        ++oldStringIt;
    }
}

static void getSubsequence(int ** grid, vector<Line>& s,
			   vector<Line>& t, vector<Line>& subsequence) {
    int sLen = s.size();
    int tLen = t.size();

    int i = 0;
    int j = 0;

    while (i < tLen && j < sLen) {
        if (s[j].equals(t[i])) {
            subsequence.push_back(s[j]);
            ++i;
            ++j;
        } else if (grid[i + 1][j] >= grid[i][j+1]) {
            ++i;
        } else {
            ++j;
        }
    }

    vector<NewLine> insertedLines;
    vector<DeletedLine> deletedLines;
    
    getInsertions(subsequence, t, insertedLines);
    getDeletions(subsequence, s, deletedLines);

    outputDiff(subsequence, insertedLines, deletedLines);
}

static void subsequenceLength(vector<Line>& s, vector<Line>& t, vector<Line>& subsequence) {
    int sLen = s.size();
    int tLen = t.size();

    int ** grid = new int * [tLen + 1];

    for (int i = 0; i <= tLen; ++i) {
        grid[i] = new int[sLen + 1];
    }

    for (int i = 0; i <= tLen; ++i) {
        for (int j = 0; j <= sLen; ++j) {
            grid[i][j] = 7;
        }
    }

    for (int i = 0; i <= tLen; ++i) {
        grid[i][sLen] = 0;
    }

    for (int j = 0; j <= sLen; ++j) {
        grid[tLen][j] = 0;
    }

    for (int i = tLen - 1; i >= 0; --i) {
        for (int j = sLen - 1; j >= 0; --j) {
            if (t[i].equals(s[j])) {
                grid[i][j] = grid[i + 1][j + 1] + 1;
            } else {
                grid[i][j] = max(grid[i + 1][j], grid[i][j + 1]);
            }
        }
    }

    getSubsequence(grid, s, t, subsequence);
    
    for (int i = 0; i <= tLen; ++i) {
        delete[] grid[i];
    }

    delete[] grid;
}

void SubsequenceAnalyzer::calculateSubsequence(vector<Line>& s, vector<Line>& t,
                                               vector<Line>& subsequence) {
    subsequenceLength(s, t, subsequence);
}
