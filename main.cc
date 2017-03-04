#include <iostream>
#include <vector>

#include "Diff.h"
#include "FileParser.h"
#include "Line.h"
#include "SubsequenceAnalyzer.h"

int main() {
    std::vector<Line> v;
    std::vector<Line> w;

    FileParser::readFile("testFile.txt", v);
    FileParser::readFile("testFile2.txt", w);

    SubsequenceAnalyzer::calculateDiff(v, w);    
    return 0;
}
