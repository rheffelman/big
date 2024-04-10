#pragma once
#include <string>
#include "SafeArrayException.h"
using namespace std;
template < class T >

class SafeArrayInt {
public:
int index = 0;
T* allVals = new T[10];
int totalSize = 10;
//--
~SafeArrayInt(){
    delete[] allVals;
}
//--
erase(int pos){
    T* newAr = new T[totalSize];
    for (int i = 0; i < (totalSize/2); i++){
        if (i != pos) newAr[i] = allVals[i];
    }
    delete[] allVals;
    allVals = newAr; 
}
//--
resize(){
    
}
//--
void push_back(int newVal){
    if (index == totalSize - 1) doubleAr();
    allVals[index] = newVal;
    index++;
}
//--
void pop_back(){
    if(index == 0) {
    SafeArrayException ex("Nothing to pop back!");
    throw ex;
}

    if (index == totalSize / 4) halfAr();
    allVals[index] = -1;
    index--;
}
//--
int size(){
    return index + 1;
}
//--
T& at(int pos){
    if (pos > index - 1 or pos < 0){
        SafeArrayException ex("Out of Bounds!");
        printf("%s\n", ex.getStr());
        throw ex;
    }
    return allVals[pos];
}
//--
T& operator[](int pos){
    return at(pos);
}
//--
private:
void doubleAr(){
    totalSize *= 2;
    T* newAr = new T[totalSize];
    for (int i = 0; i < (totalSize/2); i++) newAr[i] = allVals[i];
    delete[] allVals;
    allVals = newAr; 
}
//--
void halfAr(){
    totalSize /= 2;
    T* newAr = new T[totalSize];
    for (int i = 0; i < index; i++) newAr[i] = allVals[i];
    delete[] allVals;
    allVals = newAr;
}
};

// #include "SafeArrayInt.h"

// SafeArrayInt::~SafeArrayInt(){
//     delete [] allVals;
// }
// //--
// void SafeArrayInt::doubleAr(){
//     totalSize *= 2;
//     int* newAr = new int[totalSize];
//     for (int i = 0; i < (totalSize/2); i++) newAr[i] = allVals[i];
//     delete[] allVals;
//     allVals = newAr; 
// }
// //--
// void SafeArrayInt::halfAr(){
//     totalSize /= 2;
//     int* newAr = new int[totalSize];
//     for (int i = 0; i < index; i++) newAr[i] = allVals[i];
//     delete[] allVals;
//     allVals = newAr;
// }
// //--
// void SafeArrayInt::push_back(int newVal){
//     if (index == totalSize - 1) doubleAr();
//     allVals[index] = newVal;
//     index++;
// }
// //--
// void SafeArrayInt::pop_back(){
//     if (index == totalSize / 4) halfAr();
//     allVals[index] = -1;
//     index--;
// }
// //--
// int& SafeArrayInt::at(int pos){
//     if (pos > index - 1 or pos < 0) exit(0);
//     return allVals[pos];
// }
// //--
// int& SafeArrayInt::operator[](int pos){
//     return at(pos);
// }
// //--
// int SafeArrayInt::size(){
//     return index + 1;
// }