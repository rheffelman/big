#include <iostream>
using namespace std;

bool isLeapYear(int year){
    if (year % 400 == 0) return true;
    else if (year % 100 == 0) return false;
    else if (year % 4 == 0) return true;
    else return false;
}
int main() {
    int testYear = 1900;

    if (isLeapYear(testYear)) {
        cout << testYear << " is a leapyear" << endl;
    } else {
        cout << testYear << " is NOT a leapyear" << endl;
    }
}