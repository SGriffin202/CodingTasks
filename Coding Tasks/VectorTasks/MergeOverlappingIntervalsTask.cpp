#include "MergeOverlappingIntervalsTask.h"

using namespace std;

MergeOverlappingIntervalsTask::MergeOverlappingIntervalsTask(string nameInput, const string& testFilePath)
    : VectorTasks(nameInput)
{
    LoadTests(testFilePath);
    RunTests();
    OutputResults();
}

MergeOverlappingIntervalsTask::~MergeOverlappingIntervalsTask()
{
}

void MergeOverlappingIntervalsTask::ResetTests()
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
  "intervals": [
    [1, 2],
    [3, 5],
    [4, 7],
    [6, 8],
    [9, 10]
  ],
  "expectedOutput": [
    [1, 2],
    [3, 8],
    [9, 10]
  ]
}

*/
bool MergeOverlappingIntervalsTask::LoadTests(const string& testFilePath)
{
    ResetTests();

    ifstream stream(testFilePath);
    string line;

    bool foundIntervals = false;
    bool foundExpectedOutput = false;
    bool loadIntervals = false;
    bool loadExpectedOutput = false;

    dblVecInt input  {};
    dblVecInt output {};

    size_t delimPos = 0;
    std::string delimiter = "[";

    while (getline(stream, line))
    {
        if (line.find("  ]") != string::npos)
        {
            loadIntervals = false;
            loadExpectedOutput = false;
        }
        else if (loadIntervals || loadExpectedOutput)
        {
            if ( (delimPos = line.find(delimiter)) != string::npos )
            {
                // Adding 1 to delimPos to remove the "["
                string arrayStr = line.substr((delimPos+1));
                vector<int> curLineVec {};
                ConvertStrToVecOfInt(arrayStr, curLineVec);

                if(loadIntervals)
                    input.push_back(curLineVec);
                else
                    output.push_back(curLineVec);
            }
        }
        else if (line.find("intervals") != string::npos)
        {
            loadIntervals = true;
            foundIntervals = true;
        }
        else if (line.find("expectedOutput") != string::npos)
        {
            loadExpectedOutput = true;
            foundExpectedOutput = true;
        }
        else if (line.find("}") != string::npos)
        {
            // We've finished loading the current test, so reset temp values
            foundIntervals = false;
            foundExpectedOutput = false;
            loadIntervals = false;
            loadExpectedOutput = false;
            input.clear();
            output.clear();
        }

        // Only add test once we have all the needed values for it
        if(foundIntervals && foundExpectedOutput && !loadIntervals && !loadExpectedOutput)
        {
            functionInputs.push_back(input);
            expectedOutputs.push_back(output);
            numTests++;
        }
    }

    return (numTests > 0);
}

void MergeOverlappingIntervalsTask::RunTests()
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

dblVecInt MergeOverlappingIntervalsTask::RunTest(int& testNum)
{
    return MergeOverlappingIntervals(functionInputs[testNum]);
}

bool MergeOverlappingIntervalsTask::CheckTest( dblVecInt & testOutput,
                                               dblVecInt & expectedOutput )
{
    return (testOutput == expectedOutput);
}

void MergeOverlappingIntervalsTask::OutputResults()
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

/*
    Task
    Write a function that takes in a non-empty array of arbitrary intervals,
    merges any overlapping intervals, and returns the new intervals in no
    particular order.

    Each interval interval is an array of two integers, with interval[0] as
    the start of the interval and interval[1] as the end of the interval.
    
    Note that back-to-back intervals aren't considered to be overlapping. For
    example, [1, 5] and [6, 7] aren't overlapping; however, [1, 6] and [6, 7]
    are indeed overlapping.

    Also note that the start of any particular interval will always be less than
    or equal to the end of that interval.

    Sample Input
    intervals = [[1, 2], [3, 5], [4, 7], [6, 8], [9, 10]]

    Sample Output
    [[1, 2], [3, 8], [9, 10]]
    // Merge the intervals [3, 5], [4, 7], and [6, 8].
    // The intervals could be ordered differently.

    Time/Space Complexity
    O(nlog(n)) time | O(n) space
*/
vector<vector<int>> MergeOverlappingIntervalsTask::MergeOverlappingIntervals(vector<vector<int>> intervals)
{
    sort( intervals.begin(), intervals.end(), [](vector<int> a, vector<int> b) { return a[0] < b[0]; } );
    
    vector<vector<int>*> mergedIntervalsPtrs{};
    vector<int> *currentInterval = &intervals[0];
    mergedIntervalsPtrs.push_back(currentInterval);
    
    for(auto &nextInterval : intervals)
    {
        int curUB = currentInterval->at(1);
        int nextLB = nextInterval[0];
        int nextUB = nextInterval[1];

        if(curUB >= nextLB)
        {
            currentInterval->at(1) = max(curUB, nextUB);
        }
        else
        {
            currentInterval = &nextInterval;
            mergedIntervalsPtrs.push_back(currentInterval);
        }
    }

    vector<vector<int>> mergedIntervals{};
    for(auto interval : mergedIntervalsPtrs)
    {
        mergedIntervals.push_back(*interval);
    }
  
    return mergedIntervals;
}