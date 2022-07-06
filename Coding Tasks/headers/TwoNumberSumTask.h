#ifndef TWONUMBERSUMTASK_H
#define TWONUMBERSUMTASK_H

#include <unordered_set>

#include "VectorTasks.h"

class TwoNumberSumTask : public VectorTasks
{
private:
    std::vector<std::vector<int>> functionInputs1;
    std::vector<int> functionInputs2;

    bool LoadTests(const std::string& testFilePath) override;
    void ResetTests() override;
    void RunTests() override;
    std::vector<int> RunTest(int& testNum);
    bool CheckTest(std::vector<int> & testOutput, std::vector<int> & expectedOutput);

    std::vector<int> TwoNumberSum(std::vector<int> & array, int& targetSum);

public:
    TwoNumberSumTask(std::string nameInput, const std::string& testFilePath);
    ~TwoNumberSumTask();

    void OutputResults() override;
};

#endif