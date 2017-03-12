#include <assert.h>

#include "DiffElement.h"

using namespace std;

DiffElement::DiffElement(const ElementType type,
			 vector<Line>& linesToAdd) : type(type) {
  assert(linesToAdd.size() != 0);

  baseStartingLine = linesToAdd[0].getNumber();
  
  for (vector<Line>::const_iterator it = linesToAdd.begin(); it !=
	 linesToAdd.end(); ++it) {
    lines.push_back(it->getString());
  }

  newStartingLine = 0;
}

DiffElement::DiffElement(const ElementType type,
			 vector<string> text) : type(type) {
  assert(text.size() != 0);
  lines = text;
}

void DiffElement::print() const {
  cout << (type == INSERTION ? "INSERTED:" : "DELETED") << " (line " <<
    baseStartingLine << ")" << endl;
  for (vector<string>::const_iterator it = lines.begin(); it != lines.end();
       ++it) {
    cout << *it << endl;
  }
}

unsigned int DiffElement::getNumLines() const {
  return lines.size();
}

unsigned int DiffElement::getBaseStartingLine() const {
  return baseStartingLine;
}

vector<string> DiffElement::getLines() const {
  return lines;
}

void DiffElement::setNewStartingLine(unsigned int newStartingLine) {
  this->newStartingLine = newStartingLine;
}

unsigned int DiffElement::getNewStartingLine() const {
  return newStartingLine;
}

void DiffElement::mergeInAdditionalChanges(unsigned int startingIndex,
					   vector<string> additionalLines) {
  if (startingIndex == newStartingLine + lines.size()) {
    // do a bunch of push backs
    lines.insert(lines.begin(), additionalLines.begin(),
		 additionalLines.begin() + additionalLines.size());
  } else {
    // otherwise, find out where in the vector you're inserting, and perform a
    // bunch of insertions at that index
  }
}
