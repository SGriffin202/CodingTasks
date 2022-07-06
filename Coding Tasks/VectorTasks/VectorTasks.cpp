/*

    This is a base class for Vector Tasks to derive from.

    Contains a common functions that other derived classes might need.

    Also contains virtual functions that need to be defined in the the derived classes.

*/

#include "VectorTasks.h"

using namespace std;

VectorTasks::VectorTasks(string nameInput) :
    instanceName(nameInput)
{

}

VectorTasks::~VectorTasks()
{
}

void VectorTasks::ResetTests()
{
    expectedOutputs.clear();
    testOutputs.clear();
    testResults.clear();
    allTestsPassed = false;
    numTests = 0;
}

bool VectorTasks::GetAllTestsPassed()
{
    return allTestsPassed;
}

void VectorTasks::ConvertStrToVecOfInt(const string& vecStr, vector<int> & vec)
{
    stringstream line_stream(vecStr);
    string element;

    while ( getline(line_stream, element, ',') )
        vec.push_back(stoi(element));
}

string VectorTasks::DisplayVector(vector<int> & output)
{
    string outputStr = "[";
    for(int i = 0; i < output.size(); i++)
    {
        outputStr += to_string(output[i]);

        if (i != output.size() - 1)
            outputStr += ", ";
    }
    outputStr += "]";
    return outputStr;
}

string VectorTasks::DisplayVector(vector<vector<int>> & output)
{
    string outputStr = "\n[";
    for(int i = 0; i < output.size(); i++)
    {
        outputStr += "\n\t";
        outputStr += DisplayVector(output[i]);

        if (i != output.size() - 1)
            outputStr += ", ";
    }
    outputStr += "\n]";
    return outputStr;
}

void VectorTasks::RunTests()
{
    cout << "Base class RunTests()" << endl;
}

bool VectorTasks::LoadTests(const string& testFilePath)
{
    cout << "Base class LoadTests()" << endl;
    return false;
}

void VectorTasks::OutputResults()
{
    cout << "Base class OutputResults()" << endl;
}