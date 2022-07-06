#ifndef MERGEOVERLAPPINGINTERVALSTASK_H
#define MERGEOVERLAPPINGINTERVALSTASK_H

#include "VectorTasks.h"

typedef std::vector<std::vector<int>> dblVecInt;

class MergeOverlappingIntervalsTask : public VectorTasks
{
private:
    std::vector<dblVecInt> functionInputs;
    std::vector<dblVecInt> expectedOutputs;
    std::vector<dblVecInt> testOutputs;

    bool LoadTests(const std::string& testFilePath) override;
    void ResetTests() override;
    void RunTests() override;
    dblVecInt RunTest(int& testNum);
    bool CheckTest(dblVecInt & testOutput, dblVecInt & expectedOutput);

    std::vector<std::vector<int>> MergeOverlappingIntervals(std::vector<std::vector<int>> intervals);

public:
    MergeOverlappingIntervalsTask(std::string nameInput, const std::string& testFilePath);
    ~MergeOverlappingIntervalsTask();

    void OutputResults() override;
};

#endif