# CodingTasks
Created a program where I can run coding tasks that I have done against a set of tests defined in a seperate file.

Currently the program only has a few vector tasks to showcase it working.

Future Improvement Ideas
- The derived classes from the base class still have a lot of repeating code, particularly around the OutputResults() & RunTests() functions
- Making the FOR loop in the RunTests() function asynchronous for all the derived classes
- Have an input option in main() to say if we should run a single test / type of test (when more added in the future)
- Create a generic class for all tests types (i.e. string, binary tree, etc) so that common functions can be called (i.e. LoadTests(), RunTests(), OutputResults())
