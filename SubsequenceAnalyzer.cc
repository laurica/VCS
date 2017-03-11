#include <iostream>

#include "Diff.h"
#include "DiffApplier.h"
#include "DiffBuilder.h"
#include "DiffElement.h"
#include "SubsequenceAnalyzer.h"

using namespace std;

static void getDeltas(const vector<Line>& subsequence, const vector<Line>& alternateString,
		      DiffBuilder& builder, ElementType type) {
    vector<Line>::const_iterator altIt = alternateString.begin();
    vector<Line>::const_iterator subsequenceIt = subsequence.begin();

    // Everything contained in newString but not in subsequence is an inserted line
    while (subsequenceIt != subsequence.end()) {
      if ((*subsequenceIt).equals(*altIt)) {
          ++subsequenceIt;
          ++altIt;
      } else {
          if (type == INSERTION) {
	    builder.registerInsertedLine(subsequenceIt->getNumber(), altIt->getString());
          } else {
            builder.registerDeletedLine(altIt->getNumber(), altIt->getString());
          }
          ++altIt;
      }
    }
    
    while (altIt != alternateString.end()) {
      if (type == INSERTION) {
	unsigned int index = 0;
	if (subsequence.size() != 0) {
	  if (subsequenceIt == subsequence.end()) {
	    --subsequenceIt;
	  }
	  index = subsequenceIt->getNumber();
	}
	builder.registerInsertedLine(index, altIt->getString());
      } else {
        builder.registerDeletedLine(altIt->getNumber(), altIt->getString());
      }
      ++altIt;
    }
}

static Diff getSubsequence(int ** grid, const vector<Line>& s,
			   const vector<Line>& t, vector<Line>& subsequence) {
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

    DiffBuilder builder;
    
    getDeltas(subsequence, t, builder, INSERTION);
    getDeltas(subsequence, s, builder, DELETION);

    Diff d = builder.build();    
    return d;
}

static Diff subsequenceLength(const vector<Line>& s, const vector<Line>& t,
			      vector<Line>& subsequence) {
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
    
    Diff result = getSubsequence(grid, s, t, subsequence);
    
    for (int i = 0; i <= tLen; ++i) {
        delete[] grid[i];
    }

    delete[] grid;

    return result;
}

Diff SubsequenceAnalyzer::calculateDiff(const vector<Line>& s, const vector<Line>& t) {
    vector<Line> subsequence;
    Diff d = subsequenceLength(s, t, subsequence);
    return d;
}
