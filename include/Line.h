#ifndef LINE
#define LINE

#include <string>
#include <iostream>

class Line 
{
    unsigned int number;
    std::string line;

public:
    Line(const unsigned int i, const std::string str);
    bool equals(const Line& other) const;
    unsigned int getNumber() const;
    std::string getString() const;
    void setLineNumber(const unsigned int newNumber);
};

#endif
