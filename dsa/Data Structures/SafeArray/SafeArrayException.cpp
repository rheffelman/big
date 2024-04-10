#include "SafeArrayException.h"

SafeArrayException::SafeArrayException(string str)
{
    setStr(str);
}
//--
string SafeArrayException::getStr()
{
    return errorMessage;
}
//--
void SafeArrayException::setStr(string str)
{
    errorMessage = str;
}