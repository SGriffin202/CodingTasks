#include "LongestPeakTask.h"

using namespace std;

LongestPeakTask::LongestPeakTask(string nameInput, const string& testFilePath)
    : VectorTasks(nameInput)
{
    LoadTests(testFilePath);
    RunTests();
    OutputResults();
}

LongestPeakTask::~LongestPeakTask()
{
}

void LongestPeakTask::ResetTests()
{
    functionInputs.clear();
    expectedOutputs.clear();
    testOutputs.clear();
    testResults.clear();
    allTestsPassed = false;
    numTests = 0;
}

/*

Example input:
{
  "array": [1, 2, 3, 3, 4, 0, 10, 6, 5, -1, -3, 2, 3],
  "expectedOutput": 6
}

*/
bool LongestPeakTask::LoadTests(const string& testFilePath)
{
    ResetTests();

    ifstream stream(testFilePath);
    string line;

    bool foundArray = false;
    bool foundExpectedOutput = false;

    vector<int> input {};
    int output = 0;

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

                // It is possible to have an empty vector for the array
                if(arrayStr == "],")
                    output = {};
                else
                    ConvertStrToVecOfInt(arrayStr, input);

                foundArray = true;
            }
        }
        else if (line.find("expectedOutput") != string::npos)
        {
            if ( (delimPos = line.find(delimiter)) != string::npos )
            {
                // Adding 2 to delimPos to remove the ": "
                string arrayStr = line.substr((delimPos+2));
                output = stoi(arrayStr);
                foundExpectedOutput = true;
            }
        }
        else if (line.find("}") != string::npos)
        {
            // We've finished loading the current test, so reset temp values
            foundArray = false;
            foundExpectedOutput = false;
            input.clear();
            output = 0;
        }

        // Only add test once we have all the needed values for it
        if(foundArray && foundExpectedOutput)
        {
            functionInputs.push_back(input);
            expectedOutputs.push_back(output);
            numTests++;
        }
    }

    return (numTests > 0);
}

void LongestPeakTask::RunTests()
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

int LongestPeakTask::RunTest(int& testNum)
{
    return LongestPeak(functionInputs[testNum]);
}

bool LongestPeakTask::CheckTest(int& testOutput, int& expectedOutput)
{
    return (testOutput == expectedOutput);
}

void LongestPeakTask::OutputResults()
{
    cout << "-== Output Result for " << instanceName << " ==-" << endl << endl;
    cout << (allTestsPassed ? "All tests passed!" : "Not all tests passed!") << endl << endl;
    for(int testNum = 0; testNum < numTests; testNum++)
    {
        cout << "Test " << (testNum + 1) << ": " << (testResults[testNum] ? "Passed" : "Failed") << endl;
        cout << "Expected Output: " << expectedOutputs[testNum] << endl;
        cout << "Code Output: "     << testOutputs[testNum] << endl << endl;
    }
}


/*
    Task
    Write a function that takes in an array of integers and returns the length of
    the longest peak in the array.

    A peak is defined as adjacent integers in the array that are strictly 
    increasing until they reach a tip (the highest value in the peak), at which
    point they become strictly decreasing. At least three integers are required to
    form a peak.

    For example, the integers 1, 4, 10, 2 form a peak, but the integers 4, 0, 10 don't 
    and neither do the integers 1, 2, 2, 0. Similarly, the integers 1, 2, 3 don't
    form a peak because there aren't any strictly decreasing integers after the 3.

    Sample Input
    array = [1, 2, 3, 3, 4, 0, 10, 6, 5, -1, -3, 2, 3]

    Sample Output
    6   // 0, 10, 6, 5, -1, -3

    Time/Space Complexity
    O(n) time | O(1) space
*/
int LongestPeakTask::LongestPeak(vector<int> & array)
{
    int longestPeakLength = 0;
    int i = 1;

    while ( i < int(array.size() - 1) )
    {
        bool peakFound = (array[i] > array[i-1] && array[i] > array[i+1]);
        if(!peakFound)
        {
            i++;
            continue;
        }

        // Find how far left it goes
        int leftIdx = i - 1;
        while (leftIdx > 0 && array[leftIdx] > array[leftIdx - 1])
            leftIdx--;

        // Find how far right it goes
        int rightIdx = i + 1;
        while (rightIdx < array.size() - 1 && array[rightIdx] > array[rightIdx + 1])
            rightIdx++;

        int currentPeakLength = rightIdx - leftIdx + 1;
        longestPeakLength = max(currentPeakLength, longestPeakLength);
        i = rightIdx;
    }
  
    return longestPeakLength;
}