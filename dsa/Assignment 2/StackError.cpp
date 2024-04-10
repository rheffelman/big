#include "StackError.h"

StackError::StackError(const string& str)
{
    setStr(str);
}
//--
string StackError::getStr()
{
    return errorMessage;
}
//--
void StackError::setStr(const string& str)
{
    errorMessage = str;
}