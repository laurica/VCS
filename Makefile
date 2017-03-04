CXX = g++
CXXFLAGS = -g -MMD -Wall -std=c++11
EXEC = vcs
OBJECTS = DiffBuilder.o DiffElement.o Diff.o FileParser.o Line.o SubsequenceAnalyzer.o main.o
DEPENDS = ${OBJECTS:.o=.d}


${EXEC}: ${OBJECTS}
	${CXX} ${CXXFLAGS} ${OBJECTS} -o ${EXEC}

-include ${DEPENDS}


.PHONY: clean
clean:
	rm ${OBJECTS} ${EXEC} ${DEPENDS} 
