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
  // constructor
  DiffElement(const ElementType type, std::vector<Line>& linesToAdd);
  DiffElement(const ElementType type, std::vector<std::string> text);
  
  // getters
  unsigned int getNumLines() const;
  unsigned int getBaseStartingLine() const;
  unsigned int getNewStartingLine() const;
  std::vector<std::string> getLines() const;
  
  // setters
  void setNewStartingLine(unsigned int newStartingLine);

  // functionality
  void print() const;
  void mergeInAdditionalChanges(unsigned int startingIndex,
				std::vector<std::string> additionalLines);
};

#endif
