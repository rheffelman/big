#pragma once
#include <string>
#include <vector>
using namespace std;

class Object{
public:
    Object(int n, double d, const string& strOne, const string& strTwo);
    virtual void report() const;
    int m_n = 0;
    double m_d = 0;
    string m_strOne = "S1 error";
    string m_strTwo = "S2 error";
private:
};