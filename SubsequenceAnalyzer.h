#ifndef SUBSEQUENCEANALYZER
#define SUBSEQUENCEANALYZER

#include <vector>
#include "Line.h"
#include "NewLine.h"
#include "DeletedLine.h"

class SubsequenceAnalyzer 
{
public:
    static void calculateSubsequence(std::vector<Line>& s,
				     std::vector<Line>& t,
				     std::vector<Line>& subsequence);
};

#endif
