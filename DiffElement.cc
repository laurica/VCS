#include <assert.h>

#include "DiffElement.h"

using namespace std;

DiffElement::DiffElement(ElementType type, vector<Line>& linesToAdd) : type(type) {
  assert(linesToAdd.size() != 0);

  startingLine = linesToAdd[0].getNumber();
  
  for (vector<Line>::iterator it = linesToAdd.begin(); it != linesToAdd.end(); ++it) {
    lines.push_back(it->getString());
  }
}

void DiffElement::print() {
  cout << (type == INSERTION ? "INSERTED:" : "DELETED") << endl;
  for (vector<string>::iterator it = lines.begin(); it != lines.end(); ++it) {
    cout << *it << endl;
  }
}
