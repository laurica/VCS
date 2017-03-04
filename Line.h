#ifndef LINE
#define LINE

#include <string>
#include <iostream>

class Line 
{
friend std::ostream& operator<<(std::ostream& os, Line& l);

protected:
    int number;
    std::string str;

public:
    Line(const int i, const std::string str);
    bool equals(const Line& other) const;
    int getNumber() const;
    std::string getString() const;
    //virtual std::string toString() const;
};

std::ostream& operator<<(std::ostream& os, Line& l);

#endif
