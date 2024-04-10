#pragma once
#include <string>
using namespace std;

class StackError
{
public:

    StackError(const string& str);
    string getStr();
    void setStr(const string& str);

private:

    string errorMessage = "Exception";

};