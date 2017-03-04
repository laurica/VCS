#ifndef LINE
#define LINE

#include <string>
#include <iostream>

class Line 
{
protected:
    int number;
    std::string line;

public:
    Line(const int i, const std::string str);
    bool equals(const Line& other) const;
    int getNumber() const;
    std::string getString() const;
    virtual std::string getStringToPrint() const;
};

#endif
