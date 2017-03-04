#include "DeletedLine.h"
#include <string>

using namespace std;

DeletedLine::DeletedLine(const Line& l) : Line(l.getNumber(),
                                         "- " + l.getString()) {}

/*string DeletedLine::toString() const {
    return " - " + str;
}*/
