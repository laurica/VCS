#include <assert.h>

#include "DiffElement.h"

using namespace std;

DiffElement::DiffElement(const ElementType type,
			 const vector<Line>& linesToAdd) : type(type) {
  assert(linesToAdd.size() != 0);

  baseStartingLine = linesToAdd[0].getNumber();
  
  for (const Line& line : linesToAdd) {
    lines.push_back(line.getString());
  }
}

void DiffElement::print(ostream& os) const {
  cout << (type == INSERTION ? "inserted" : "deleted") << " - " << baseStartingLine << endl;
  for (const string& line : lines) {
    os << line << "\n";
  }

  os << flush;
}

unsigned int DiffElement::getNumLines() const {
  return lines.size();
}

unsigned int DiffElement::getBaseStartingLine() const {
  return baseStartingLine;
}

const vector<string>& DiffElement::getLines() const {
  return lines;
}
