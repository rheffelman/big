#pragma once
#include <string>
using namespace std;

class SafeArrayException{
public:
    SafeArrayException(string str);
    string getStr();
    void setStr(string str);
private:
string errorMessage = "Exception";
};