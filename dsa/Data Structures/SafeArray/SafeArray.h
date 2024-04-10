#pragma once
#include <string>
#include "SafeArrayException.h"
using namespace std;
template < typename T >
class SafeArray
{
public:

    SafeArray();
    SafeArray(int val); // constructs SafeArray of a given size (val)
    SafeArray(const SafeArray& original);
    ~SafeArray();
    void resize(int newSize);
    void erase(int pos);
    void push_back(T newVal);
    void pop_back();
    int size();
    T& at(int pos);
    T& operator[](int pos);
    
private:

    void doubleAr();
    void halveAr();
    int index;
    T* allVals;
    int totalSize;

};
//--
template < typename T >SafeArray<T>::SafeArray()
{
    index = 0;
    totalSize = 10;
    allVals = new T[totalSize];
}
//--
template < typename T >SafeArray<T>::SafeArray(int val)
{
    index = 0;
    totalSize = val;
    allVals = new T[totalSize];
}
//--
template < typename T >SafeArray<T>::SafeArray(const SafeArray& original)
{
    index = original.index;
    totalSize = original.totalSize;
    allVals = new T[totalSize];

    for (int i = 0; i < index + 1; i++)
    {
        allVals[i] = original.allVals[i];
    }
}
//--
template < typename T >SafeArray<T>::~SafeArray()
{
    delete[] allVals;
    allVals = NULL;
}
//--
template < typename T >void SafeArray<T>::resize(int newSize)
{
    delete[] allVals;
    T* newAr = new T[newSize * 2];
    index = newSize;
    allVals = newAr;
}
//--
template < typename T >void SafeArray<T>::erase(int pos)
{
    T* newAr = new T[totalSize];

    for (int i = 0; i < (totalSize/2); i++)
    {
        if (i != pos) newAr[i] = allVals[i];
    }
    delete[] allVals;
    allVals = newAr;
    pop_back();
}
//--
template < typename T >void SafeArray<T>::push_back(T newVal)
{
    if (index == totalSize - 1) doubleAr();
    allVals[index] = newVal;
    index++;
}
//--
template < typename T >void SafeArray<T>::pop_back()
{
    if(index == 0) 
    {
    SafeArrayException ex("Nothing to pop back!");
    throw ex;
    }
    if (index == totalSize / 4) halveAr();
    index--;
}
//--
template < typename T >int SafeArray<T>::size()
{
     return index;
}
//--
template < typename T >T& SafeArray<T>::at(int pos)
{
    if (pos > index - 1 or pos < 0)
    {
        SafeArrayException ex("Out of Bounds!");
        printf("%s\n", ex.getStr());
        throw ex;
    }
    return allVals[pos];
}
//--
template < typename T >T& SafeArray<T>::operator[](int pos)
{
    return at(pos);
}
//--
template < typename T >void SafeArray<T>::doubleAr()
{
    totalSize *= 2;
    T* newAr = new T[totalSize];
    for (int i = 0; i < (totalSize/2); i++) newAr[i] = allVals[i];
    delete[] allVals;
    allVals = newAr; 
}
//--
template < typename T >void SafeArray<T>::halveAr()
{
    totalSize /= 2;
    T* newAr = new T[totalSize];
    for (int i = 0; i < index; i++) newAr[i] = allVals[i];
    delete[] allVals;
    allVals = newAr;
}

/*
-insert
    O(1) if not full
    O(n) if full and inserting in the middle

-retrieve
    O(1) if you know the index
    O(n) if you don't know the index

-remove
    O(1) if removing from the end
    O(n) if removing from the end
*/
