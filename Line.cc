#include "Line.h"
#include <sstream>

using namespace std;

Line::Line(int number, string str) : number(number), str(str) {}

bool Line::equals(Line& other) {
    return str == other.str;
}

int Line::getNumber() const {
    return number;
}

string Line::getString() const {
    return str;
}

/*string Line::toString() const {
    stringstream ss;
    ss << number;
    return ss.str() + " - " + str;
}*/

ostream& operator<<(std::ostream& os, Line& l) {
    os << l.number << " " << l.str;
    return os;
}
