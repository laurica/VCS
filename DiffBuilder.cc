#include "DiffBuilder.h"

using namespace std;

static void registerNewLine(vector<Line>& lines, Line& newLine, int& lastNum,
			    vector<DiffElement>& elements, ElementType type) {
  if (lines.size() != 0 && newLine.getNumber() != lastNum + 1) {
    // create a new diff element
    elements.push_back(DiffElement(type, lines));
    // emtpy the deletedLines container
    lines.clear();
  }

  lastNum = newLine.getNumber();
  lines.push_back(newLine);
}

void DiffBuilder::registerDeletedLine(Line l) {
  registerNewLine(deletedLines, l, numberOfLastDeletedLine, deletions, DELETION);
}

void DiffBuilder::registerInsertedLine(Line l) {
  registerNewLine(insertedLines, l, numberOfLastInsertedLine, insertions, INSERTION);
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
  
  Diff d(insertions, deletions);
  
  insertions.clear();
  deletions.clear();
  return d;
}
