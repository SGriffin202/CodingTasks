/*
    Task
    Write a function that takes in a non-empty array of distinct integers and an
    integer representing a target sum. If any two numbers in the input array sum
    up to the target sum, the function should return them in an array, in any
    order. If no two numbers sum up to the target sum, the function should return
    an empty array.

    Sample Input
    Array = [3, 5, -4, 8, 11, 1, -1, 6]
    Target Sum = 10

    Sample Output
    [-1, 11]
    
*/

#include "TwoNumberSumTask.h"

using namespace std;

TwoNumberSumTask::TwoNumberSumTask(string nameInput, const string& testFilePath)
    : VectorTasks(nameInput)
{
    LoadTests(testFilePath);
    RunTests();
    OutputResults();
}

TwoNumberSumTask::~TwoNumberSumTask()
{
}

void TwoNumberSumTask::ResetTests()
{
    functionInputs1.clear();
    functionInputs2.clear();
    expectedOutputs.clear();
    testOutputs.clear();
    testResults.clear();
    allTestsPassed = false;
    numTests = 0;
}

/*

Example input:
{
  "array": [4, 6, 1, -3],
  "targetSum": 3,
  "expectedOutput": [-3, 6]
}

*/
bool TwoNumberSumTask::LoadTests(const string& testFilePath)
{
    ResetTests();

    ifstream stream(testFilePath);
    string line;

    bool foundArray = false;
    bool foundTargetSum = false;
    bool foundExpectedOutput = false;

    vector<int> input1 {};
    int input2 = 0;
    vector<int> output {};

    size_t delimPos = 0;
    std::string delimiter = ":";

    while (getline(stream, line))
    {
        if (line.find("array") != string::npos)
        {
            if ( (delimPos = line.find(delimiter)) != string::npos )
            {
                // Adding 3 to delimPos to remove the ": ["
                string arrayStr = line.substr((delimPos+3));
                ConvertStrToVecOfInt(arrayStr, input1);
                foundArray = true;
            }
        }
        else if (line.find("targetSum") != string::npos)
        {
            if ( (delimPos = line.find(delimiter)) != string::npos )
            {
                // Adding 2 to delimPos to remove the ": "
                string intStr = line.substr((delimPos+2));
                input2 = stoi(intStr);
                foundTargetSum = true;
            }
        }
        else if (line.find("expectedOutput") != string::npos)
        {
            if ( (delimPos = line.find(delimiter)) != string::npos )
            {
                // Adding 3 to delimPos to remove the ": ["
                string arrayStr = line.substr((delimPos+3));

                // It is possible to have an empty vector for the expectedOutput
                if(arrayStr == "]")
                    output = {};
                else
                    ConvertStrToVecOfInt(arrayStr, output);

                foundExpectedOutput = true;
            }
        }
        else if (line.find("}") != string::npos)
        {
            // We've finished loading the current test, so reset temp values
            foundArray = false;
            foundTargetSum = false;
            foundExpectedOutput = false;
            input1.clear();
            input2 = 0;
            output.clear();
        }

        // Only add test once we have all the needed values for it
        if(foundArray && foundTargetSum && foundExpectedOutput)
        {
            functionInputs1.push_back(input1);
            functionInputs2.push_back(input2);
            expectedOutputs.push_back(output);
            numTests++;
        }
    }

    return (numTests > 0);
}

void TwoNumberSumTask::RunTests()
{
    allTestsPassed = true;
    
    for(int testNum = 0; testNum < numTests; testNum++)
    {
        auto testOutput = RunTest(testNum);
        bool testResult = CheckTest(testOutput, expectedOutputs[testNum]);

        testOutputs.push_back(testOutput);
        testResults.push_back(testResult);

        if (!testResult)
            allTestsPassed = false;
    }
}

vector<int> TwoNumberSumTask::RunTest(int& testNum)
{
    return TwoNumberSum(functionInputs1[testNum], functionInputs2[testNum]);
}

bool TwoNumberSumTask::CheckTest(vector<int> & testOutput, vector<int> & expectedOutput)
{
    bool testPassed = true;

    for(auto element : expectedOutput)
    {
        if( find(testOutput.begin(), testOutput.end(), element) == testOutput.end() )
            testPassed = false;
    }

    return testPassed;
}

void TwoNumberSumTask::OutputResults()
{
    cout << "-== Output Result for " << instanceName << " ==-" << endl << endl;
    cout << (allTestsPassed ? "All tests passed!" : "Not all tests passed!") << endl << endl;
    for(int testNum = 0; testNum < numTests; testNum++)
    {
        cout << "Test " << (testNum + 1) << ": " << (testResults[testNum] ? "Passed" : "Failed") << endl;
        cout << "Expected Output: " << DisplayVector(expectedOutputs[testNum]) << endl;
        cout << "Code Output: "     << DisplayVector(testOutputs[testNum]) << endl << endl;
    }
}

//    Time/Space Complexity
//    O(n) Time | O(n) Space
//
vector<int> TwoNumberSumTask::TwoNumberSum(vector<int> & array, int& targetSum)
{
    vector<int> retVal {};
    unordered_set<int> numbersPast;

    for(int num : array)
    {
        int searchNum = targetSum - num;
        if ( numbersPast.find(searchNum) != numbersPast.end() )
        {
            retVal = {num, searchNum};
            break;
        }
        else
            numbersPast.insert(num);
    }

    return retVal;
}