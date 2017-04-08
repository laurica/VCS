#ifndef SUBSEQUENCEANALYZER
#define SUBSEQUENCEANALYZER

#include <vector>

#include "Diff.h"
#include "Line.h"

class SubsequenceAnalyzer 
{
public:
    static Diff calculateDiff(const std::vector<Line>& s, const std::vector<Line>& t);
};

#endif
