#ifndef INTERPRETOR
#define INTERPRETOR

#include <sstream>
#include <string>

#include "OperationAccumulator.h"

class Interpretor {
  OperationAccumulator& accumulator;

  bool parseInit(std::istringstream& input) const;
  bool parseFirstCommand(const std::string& command) const;
  void parseCommand(const std::string& command) const;
  void parseAdd(std::istringstream& input) const;
  
 public:
  Interpretor(OperationAccumulator& accumulator);
  void interpret() const;
};

#endif
