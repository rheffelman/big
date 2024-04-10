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
string DoTW(string date);
int yearVal(int year);
int dayVal(int day);
int monthVal(int month);
int centuryVal(int year);
int main() {
    string startDate = "3/19/1973";
    string endDate = "2/17/2023";
    int meetings = 25;
    printf("The dates of the %d meetings between %s and %s are:\n", meetings, startDate.c_str(), endDate.c_str());
    printDatesInBetween(startDate, endDate, meetings);
}
string DoTW(string date){
    int month; int day; int year;
    parseDate(date, month, day, year);
    if (year / 100 == 17){
        return "";
    }
    int monthValue = monthVal(month);
    int dayValue = dayVal(day);
    int centuryValue = centuryVal(year);
    int yearValue = yearVal(year);
    int DoTWVal = monthValue+ dayValue+yearValue+centuryValue;
    if (month == 2 and isLeapYear(year) == true){
        DoTWVal -= 1;
    }
    while (DoTWVal >= 0 and DoTWVal > 6){
        DoTWVal -= 7;
    }
    string dayArray[7] {"Saturday, ", "Sunday, ", "Monday, ", "Tuesday, ", "Wednesday, ", "Thursday, ", "Friday, "};
    return dayArray[DoTWVal];
}
int yearVal(int year){
    year %= 100;
    year %= 28;
    int valArray[28] {0, 1, 2, 3, 5, 6, 0, 1, 3, 4, 5, 6, 1, 2, 3, 4, 6, 0, 1, 2, 4, 5, 6, 0, 2, 3, 4, 5};
    return valArray[year];
}
int dayVal(int day){
    while (day >= 0 and day > 6){
        day -= 7;
    }
    return day;
}
int monthVal(int month){
    if (month == 2 or month == 3 or month == 11){
        return 4;
    }
    else if (month == 4 or month == 7){
        return 0;
    }
    else if (month == 1 or month == 10){
        return 1;
    }
    else if (month == 12 or month == 9){
        return 6;
    }
    else if (month == 5){
        return 2;
    }
    else if (month == 8){
        return 3;
    }
    else return 5;
}
int centuryVal(int year){
    int century = year / 100;
        if (century > 17){
            if (century % 4 == 1){
                return 4;
            }
            else if (century % 4 == 2){
                return 2;
            }
            else if (century % 4 == 0){
                return 6;
            }
            else return 0;
        }
        else if (century < 17){
            int returnVal = 2;
            for (int i = 16; true; i--){
                if (returnVal > 6){
                    returnVal = 0;
                }
                if (i == century){
                    return returnVal;
                }
                returnVal++;
            }
        }
}
void printDatesInBetween(string startDate, string endDate, int numberOfMeetings){
    int interval = calcInterval(startDate, endDate, numberOfMeetings);
    int n = intFromDate(startDate);
    for (int i = 0; i < numberOfMeetings; i++){
        printf("%d) %s%s\n",i+1, DoTW(dateFromInt(n)).c_str(), dateFromInt(n).c_str());
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
