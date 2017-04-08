#ifndef INTERPRETOR
#define INTERPRETOR

#include <sstream>
#include <string>
#include <vector>

#include "OperationAccumulator.h"

class Interpretor {
  enum ErrorMessage {
    UNRECOGNIZED_COMMAND,
    NOT_ENOUGH_ARGS,
    TOO_MANY_ARGS,
    FILE_NOT_FOUND,
    PROJECT_ALREADY_INITIALIZED,
    PROJECT_UNINITIALIZED
  };

  std::map<ErrorMessage, const char *> errorMessages;
  
  OperationAccumulator& accumulator;

  bool parseInit(std::istringstream& input) const;
  bool parseFirstCommand(const std::string& command) const;
  void parseCommand(const std::string& command) const;
  void parseAdd(std::istringstream& input) const;
  bool parseOneArgument(std::istringstream& input, std::string& arg) const;
  
 public:
  Interpretor(OperationAccumulator& accumulator);
  void interpret() const;
};

#endif
