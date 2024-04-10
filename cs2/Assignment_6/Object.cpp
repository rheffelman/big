#include "Object.h"

Object::Object(int n, double d, const string& strOne, const string& strTwo){
    m_n = n;
    m_d = d;
    m_strOne = strOne;
    m_strTwo = strTwo;
}
//--
void Object::report() const{
    printf("Name: %s\n", m_strOne.c_str());
    printf("Address: %s\n", m_strTwo.c_str());
    printf("Account Number: %d\n", m_n);
    printf("Account Balance: $%.2f\n", m_d);
}