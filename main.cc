#include "Interpretor.h"
#include "OperationAccumulator.h"

int main() {
  OperationAccumulator accumulator;
  Interpretor interpretor(accumulator);
  interpretor.interpret();
  accumulator.saveState();
  return 0;
}
