#include <iostream>

#include "TwoNumberSumTask.h"
#include "MergeOverlappingIntervalsTask.h"
#include "LongestPeakTask.h"

using namespace std;

int main()
{
    bool allTestsPassed = true;
    cout << "Coding Tasks" << endl;

    TwoNumberSumTask TwoNumSum("Two Number Sum", "Tests/TwoNumberSumTest.txt");
    allTestsPassed = (allTestsPassed && TwoNumSum.GetAllTestsPassed());

    MergeOverlappingIntervalsTask MOI("Merge Overlapping Intervals", "Tests/MergeOverlappingIntervalsTests.txt");
    allTestsPassed = (allTestsPassed && MOI.GetAllTestsPassed());

    LongestPeakTask LP("Longest Peak", "Tests/LongestPeakTest.txt");
    allTestsPassed = (allTestsPassed && LP.GetAllTestsPassed());

    cout << "VectorTasks allTestsPassed: " << (allTestsPassed ? "Yes" : "No") << endl;

    return 0;
}
