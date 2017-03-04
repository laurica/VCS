#include "NewLine.h"

using namespace std;

NewLine::NewLine(const Line& l) : Line(l.getNumber(), l.getString()) {}

string NewLine::getStringToPrint() const {
  return "+ " + line;
}
