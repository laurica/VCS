#include "Interpretor.h"
#include "OperationAccumulator.h"

int main() {
  OperationAccumulator accumulator;
  if (!accumulator.initialize()) {
    return 1;
  }
  
  Interpretor interpretor(accumulator);
  interpretor.interpret();
  accumulator.saveState();
  return 0;
}
