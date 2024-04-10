#include <iostream>
#include <string>
using namespace std;

bool isLeapYear(int year);
int getNumberOfDaysInYear(int year);
int getDaysInMonth(int month, int year);
void parseDate(string dateString, int& monthNum, int& dayNum, int& yearNum);
int intFromDate(string date);
string dateFromInt(int days);
int calcInterval(string startDate, string endDate, int meetingNum);
void printDatesInBetween(string startDate, string endDate, int numberOfMeetings);

int main() {
    string startDate = "3/19/1973";
    string endDate = "2/17/2023";
    int meetings = 25;
    printf("The dates of the %d meetings between %s and %s are:\n", meetings, startDate.c_str(), endDate.c_str());
    printDatesInBetween(startDate, endDate, meetings);
}
void printDatesInBetween(string startDate, string endDate, int numberOfMeetings){
    int interval = calcInterval(startDate, endDate, numberOfMeetings);
    int n = intFromDate(startDate);
    for (int i = 0; i < numberOfMeetings; i++){
        printf("%d) %s\n",i+1, dateFromInt(n).c_str());
        n += interval;
    }
}
int calcInterval(string startDate, string endDate, int meetingNum){
    int difference = intFromDate(endDate) - intFromDate(startDate);
    return difference / (meetingNum - 1);
}
int intFromDate(string date){
    int month; int day; int year;
    parseDate(date, month, day, year);
    int sum = day - 1;
    for (int i = 1; i < year; i++){
        sum += getNumberOfDaysInYear(i);
    }
    for (int i = 1; i < month; i++){
        sum += getDaysInMonth(i, year);
    }
    return sum;
}
string dateFromInt(int number){
    int months = 1; int days; int years = 0;
    for (int i = 1; number > 366; i++){
        number -= getNumberOfDaysInYear(i);
        years = i + 1;
    }
    for (int i = 1; number >= getDaysInMonth(i, years); i++){
        number -= getDaysInMonth(i, years);
        months = i + 1;
    }
    days = number + 1;
    string returnString = to_string(months) + "/" + to_string(days) + "/" + to_string(years);
    return returnString;
}
void parseDate(string dateString, int& monthNum, int& dayNum, int& yearNum)
{
    string monthString = "";
    string dayString = "";
    string yearString = "";
    int count = 0;

    //  months
    for (int i = 0; i < dateString.length(); i++){
        if (dateString[i] != '/'){
            monthString += dateString[i];
            count++;
        }
        else if (dateString[i] == '/'){
            count++;
            break;
        }
    }

    //  days
    for (int i = count; i < dateString.length(); i++) {
        if (dateString[i] != '/') {
            dayString += dateString[i];
            count++;
        } else if (dateString[i] == '/') {
            count++;
            break;
        }
    }

    //  years
    for (int i = count; i < dateString.length(); i++){
        if (dateString[i] != '/'){
            yearString += dateString[i];
            count++;
        }
        else if (dateString[i] == '/'){
            count++;
            break;
        }
    }
    monthNum = stoi(monthString);
    dayNum = stoi(dayString);
    yearNum = stoi(yearString);
}
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
