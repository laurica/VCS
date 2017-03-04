#ifndef SUBSEQUENCEANALYZER
#define SUBSEQUENCEANALYZER

#include <vector>

#include "Diff.h"
#include "Line.h"

class SubsequenceAnalyzer 
{
public:
    static Diff calculateDiff(std::vector<Line>& s, std::vector<Line>& t,
			      std::vector<Line>& subsequence);
};

#endif
