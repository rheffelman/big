#include <iostream>
using namespace std;

bool isLeapYear(int year){
    if (year % 400 == 0) return true;
    else if (year % 100 == 0) return false;
    else if (year % 4 == 0) return true;
    else return false;
}

int getNumberOfDaysInYear(int year){
    if (isLeapYear(year) == true) return 366;
    else return 365;
}
int getDaysInMonth(int month, int year){
    if (month == 1 or month == 3 or month == 5 or month == 7 or month == 8 or month == 10 or month == 12){
        return 31;
    }
    else if (month == 4 or month == 6 or month == 9 or month == 11){
        return 30;
    }
    else if (isLeapYear(year) == true) return 29;
    else return 28;
}
int main() {
    cout<<"Number of days: "<<getDaysInMonth(1, 2020)<<endl; //should print 31
    cout<<"Number of days: "<<getDaysInMonth(2, 2020)<<endl; //should print 29
    cout<<"Number of days: "<<getDaysInMonth(11, 2021)<<endl; //should print 30
    cout<<"Number of days: "<<getDaysInMonth(2, 2021)<<endl; //should print 28
}