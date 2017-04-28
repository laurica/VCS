#ifndef DIFFELEMENT
#define DIFFELEMENT

#include <iostream>
#include <vector>

#include "Line.h"

enum ElementType {
  INSERTION,
  DELETION
};

class DiffElement {
  const ElementType type;
  std::vector<std::string> lines;
  // starting line is the line in the previous file this change occurs on
  unsigned int baseStartingLine;
  
 public:
  // constructor
  DiffElement(const ElementType type, const std::vector<Line>& linesToAdd);
  unsigned int getNumLines() const;
  const std::vector<std::string>& getLines() const;
  unsigned int getBaseStartingLine() const;
  void print(std::ostream& os) const;
};

#endif
