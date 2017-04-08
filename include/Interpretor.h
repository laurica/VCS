#ifndef INTERPRETOR
#define INTERPRETOR

#include <sstream>
#include <string>

#include "OperationAccumulator.h"

class Interpretor {
  OperationAccumulator& accumulator;

  bool parseInit(std::istringstream& input);
  bool parseFirstCommand(const std::string& command);
  
 public:
  Interpretor(OperationAccumulator& accumulator);
  void interpret();
};

#endif
