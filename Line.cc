#include "Line.h"
#include <sstream>

using namespace std;

Line::Line(const int number, const string str) : number(number), line(str) {}

bool Line::equals(const Line& other) const {
    return line == other.line;
}

int Line::getNumber() const {
    return number;
}

string Line::getString() const {
    return line;
}
