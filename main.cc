#include "FileParser.h"
#include <vector>
#include "SubsequenceAnalyzer.h"
#include <iostream>
#include "Line.h"

int main() {
    std::vector<Line> v;
    std::vector<Line> w;
    std::vector<Line> sub;

    FileParser::readFile("testFile.txt", v);
    FileParser::readFile("testFile2.txt", w);

    SubsequenceAnalyzer::calculateSubsequence(v, w, sub);

    return 0;
}
