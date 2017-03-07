#include <assert.h>

#include "DiffElement.h"

using namespace std;

DiffElement::DiffElement(const ElementType type, const vector<Line>& linesToAdd) :
  type(type) {
  assert(linesToAdd.size() != 0);

  startingLine = linesToAdd[0].getNumber();
  
  for (vector<Line>::const_iterator it = linesToAdd.begin(); it != linesToAdd.end(); ++it) {
    lines.push_back(it->getString());
  }
}

void DiffElement::print() const {
  cout << (type == INSERTION ? "INSERTED:" : "DELETED") << endl;
  for (vector<string>::const_iterator it = lines.begin(); it != lines.end(); ++it) {
    cout << *it << endl;
  }
}

int DiffElement::getNumLines() const {
  return lines.size();
}

int DiffElement::getStartingLine() const {
  return startingLine;
}

const vector<string>& DiffElement::getLines() const {
  return lines;
}
