CXX = g++
CXXFLAGS = -g -MMD -Wall -std=c++11
EXEC = vcs
OBJECTS = DiffApplier.o DiffBuilder.o DiffElement.o Diff.o FileParser.o FileWriter.o Interpretor.o Line.o OperationAccumulator.o SubsequenceAnalyzer.o main.o
DEPENDS = ${OBJECTS:.o=.d}


${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}


.PHONY: clean
clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS} 
