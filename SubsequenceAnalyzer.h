#ifndef SUBSEQUENCEANALYZER
#define SUBSEQUENCEANALYZER

#include <vector>
#include "Line.h"
#include "NewLine.h"
#include "DeletedLine.h"

class SubsequenceAnalyzer 
{
private:
    void subsequenceLength(std::vector<Line>& s,
                           std::vector<Line>& t,
                           std::vector<Line>& subsequence);
    
    void getSubsequence(int ** grid, std::vector<Line>& s, 
                        std::vector<Line>& t, 
                        std::vector<Line>& subsequence);

    void getInsertions(std::vector<Line>& subsequence, 
                       std::vector<Line>& newString, 
                       std::vector<NewLine>& insertedLines);

    void getDeletions(std::vector<Line>& subsequence,
                      std::vector<Line>& oldString,
                      std::vector<DeletedLine>& deletedLines);
    
    void outputDiff(std::vector<Line>& subsequence,
                    std::vector<NewLine>& insertions,
                    std::vector<DeletedLine>& deletions);

public:
    void calculateSubsequence(std::vector<Line>& s,
                              std::vector<Line>& t,
                              std::vector<Line>& subsequence);
};

#endif
