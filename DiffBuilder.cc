#include "DiffBuilder.h"

using namespace std;

static void registerNewLine(vector<Line>& lines, const Line& newLine, unsigned int& lastNum,
			    vector<DiffElement>& elements, const ElementType type) {
  if (lines.size() != 0 && newLine.getNumber() != (type == INSERTION ? lastNum : lastNum + 1)) {
    // create a new diff element
    elements.push_back(DiffElement(type, lines));
    // emtpy the deletedLines container
    lines.clear();
  }

  lastNum = newLine.getNumber();
  lines.push_back(newLine);
}

void DiffBuilder::registerDeletedLine(const unsigned int index, const std::string& text) {
  registerNewLine(deletedLines, Line(index, text), numberOfLastDeletedLine, deletions, DELETION);
}

void DiffBuilder::registerInsertedLine(const unsigned int index, const std::string& text) {
  registerNewLine(insertedLines, Line(index, text), numberOfLastInsertedLine, insertions, INSERTION);
}

static void addFinalElementAndClear(vector<Line>& lines, vector<DiffElement>& elements,
				    ElementType type) {
  if (lines.size() != 0) {
    elements.push_back(DiffElement(type, lines));
    lines.clear();
  }
}

Diff DiffBuilder::build() {
  // If there is anything in the inserted/deleted line vectors, generate another diff
  // element.
  addFinalElementAndClear(deletedLines, deletions, DELETION);
  addFinalElementAndClear(insertedLines, insertions, INSERTION);

  // now we need to properly set the 'new line number' field of the diff elements
  // this only applies to insertions (deleted lines don't have anything corresponding in the new file)
  vector<DiffElement>::iterator it = insertions.begin();
  vector<DiffElement>::iterator delIt = deletions.begin();
  int curDelta = 0;
  
  while (it != insertions.end()) {
    unsigned int tempDelta = 0;
    // take as many deletions as we can
    while (delIt != deletions.end() && delIt->getBaseStartingLine() < it->getBaseStartingLine()) {
      tempDelta += delIt->getNumLines();
      ++delIt;
    }

    curDelta -= tempDelta;
    it->setNewStartingLine(it->getBaseStartingLine() + curDelta);

    if (delIt != deletions.end() && delIt->getBaseStartingLine() == it->getBaseStartingLine()) {
      curDelta -= delIt->getNumLines();
      ++delIt;
    }

    curDelta += it->getNumLines();
    
    ++it;
  }
  
  Diff d(insertions, deletions);
  
  insertions.clear();
  deletions.clear();
  return d;
}
