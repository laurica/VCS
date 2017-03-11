#ifndef DIFFELEMENT
#define DIFFELEMENT

#include <vector>

#include "Line.h"

enum ElementType {
  INSERTION,
  DELETION
};

class DiffElement {
  ElementType type;
  std::vector<std::string> lines;
  // starting line is the line in the previous file this change occurs on
  unsigned int baseStartingLine;
  unsigned int newStartingLine;
  
 public:
  void print() const;
  unsigned int getNumLines() const;
  unsigned int getBaseStartingLine() const;
  void setNewStartingLine(unsigned int newStartingLine);
  unsigned int getNewStartingLine() const;
  const std::vector<std::string>& getLines() const;
  DiffElement(const ElementType type, const std::vector<Line>& linesToAdd);
};

#endif
