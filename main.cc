#include "FileParser.h"
#include <vector>
#include "SubsequenceAnalyzer.h"
#include <iostream>
#include "Line.h"

int main() {
    std::vector<Line> v;
    std::vector<Line> w;
    std::vector<Line> sub;

    FileParser f;
    SubsequenceAnalyzer s;
    f.readFile("testFile.txt", v);
    f.readFile("testFile2.txt", w);

    s.calculateSubsequence(v, w, sub);

    return 0;
}
