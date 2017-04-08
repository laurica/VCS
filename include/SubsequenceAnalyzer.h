#ifndef SUBSEQUENCEANALYZER
#define SUBSEQUENCEANALYZER

#include <vector>

#include "FileDiff.h"
#include "Line.h"

class SubsequenceAnalyzer 
{
public:
    static FileDiff calculateDiff(const std::vector<Line>& s,
				  const std::vector<Line>& t);
};

#endif
