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
int main() {
    int sum = 0;
    for (int i = 1900; i <= 1999; i++){
        sum += getNumberOfDaysInYear(i);
    }
    printf("%d", sum);
}