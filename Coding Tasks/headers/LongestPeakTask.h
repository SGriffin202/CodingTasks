#ifndef LONGESTPEAKTASK_H
#define LONGESTPEAKTASK_H

#include "VectorTasks.h"

class LongestPeakTask : public VectorTasks
{
private:
    std::vector<std::vector<int>> functionInputs;
    std::vector<int>              expectedOutputs;
    std::vector<int>              testOutputs;

    bool LoadTests(const std::string& testFilePath) override;
    void ResetTests() override;
    void RunTests() override;
    int RunTest(int& testNum);
    bool CheckTest(int& testOutput, int& expectedOutput);

    int LongestPeak(std::vector<int> & array);

public:
    LongestPeakTask(std::string nameInput, const std::string& testFilePath);
    ~LongestPeakTask();

    void OutputResults() override;
};

#endif