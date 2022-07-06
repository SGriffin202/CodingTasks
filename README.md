# CodingTasks
Created a program to read in a test file for a programming task and evaluate each test case against my solution to the task.

Currently the program only has a few vector tasks to showcase it working.

The description of the tasks that the code is testing can be found at the top of each of the .cpp task files (LongestPeakTask.cpp, MergeOverlappingIntervalsTask.cpp, TwoNumberSumTask.cpp).

Future Improvement Ideas
- The derived classes from the base class still have a lot of repeating code, particularly around the OutputResults() & RunTests() functions
- Making the FOR loop in the RunTests() function asynchronous for all the derived classes
- Have an input option in main() to say if we should run a single test / type of test (when more added in the future)
- Create a generic class for all tests types (i.e. string, binary tree, etc) so that common functions can be called (i.e. LoadTests(), RunTests(), OutputResults())
