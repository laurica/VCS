#include "DeletedLine.h"

using namespace std;

DeletedLine::DeletedLine(const Line& l) : Line(l.getNumber(), l.getString()) {}

string DeletedLine::getStringToPrint() const {
  return "- " + line;
}
