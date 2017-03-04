#include <iostream>
#include <vector>

#include "FileParser.h"
#include "Line.h"
#include "SubsequenceAnalyzer.h"

int main() {
    std::vector<Line> v;
    std::vector<Line> w;
    std::vector<Line> sub;

    FileParser::readFile("testFile.txt", v);
    FileParser::readFile("testFile2.txt", w);

    SubsequenceAnalyzer::calculateDiff(v, w, sub);
    
    return 0;
}
