#ifndef NEWLINE
#define NEWLINE

#include "Line.h"
#include <string>

class NewLine : public Line {
public:
    NewLine(const Line& l);
    std::string getStringToPrint() const override;
};

#endif
