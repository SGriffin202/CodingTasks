#ifndef VECTORTASKS_H
#define VECTORTASKS_H

#include <algorithm>
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

class VectorTasks
{
protected:
    std::vector<std::vector<int>> expectedOutputs;
    std::vector<std::vector<int>> testOutputs;
    std::vector<bool>             testResults;
    bool                          allTestsPassed;
    int                           numTests;
    std::string                   instanceName;

    virtual bool LoadTests(const std::string& testFilePath);
    virtual void ResetTests();
    virtual void RunTests();
    std::string DisplayVector(std::vector<int> & output);
    std::string DisplayVector(std::vector<std::vector<int>> & output);
    void ConvertStrToVecOfInt(const std::string& vecStr, std::vector<int> & vec);

public:
    VectorTasks(std::string nameInput);
    ~VectorTasks();

    bool GetAllTestsPassed();
    virtual void OutputResults();
};

#endif