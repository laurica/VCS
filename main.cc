#include <iostream>
#include <vector>

#include "Diff.h"
#include "DiffApplier.h"
#include "FileParser.h"
#include "FileWriter.h"
#include "Line.h"
#include "SubsequenceAnalyzer.h"

int main() {
    std::vector<Line> v;
    std::vector<Line> w;

    FileParser::readFile("examples/diff1.cpp", v);
    FileParser::readFile("examples/diff2.cpp", w);

    Diff d = SubsequenceAnalyzer::calculateDiff(v, w);
    std::vector<Line> newFile;
    DiffApplier::applyDiff(v, d, newFile);

    FileWriter::writeFile(newFile, "testing01.txt");
    
    return 0;
}
