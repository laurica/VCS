#ifndef DELETEDLINE
#define DELETEDLINE

#include "Line.h"
#include <string>

class DeletedLine : public Line {
public:
    DeletedLine(const Line& l);
    std::string getStringToPrint() const override;
};

#endif
