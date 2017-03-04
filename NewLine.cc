#include "NewLine.h"
#include <string>

using namespace std;

NewLine::NewLine(const Line& l) : Line(l.getNumber(), "+ " + l.getString()) {}

/*string NewLine::toString() const {
    return " + " + getString();
    }*/

