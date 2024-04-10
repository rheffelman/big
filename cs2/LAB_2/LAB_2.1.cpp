#include <iostream>
#include <string>
using namespace std;

void parseDate(string dateString, int& monthNum, int& dayNum, int& yearNum);

int main() {
    int month;
    int day;
    int year;

    parseDate("3/19/1973", month, day, year);
    cout<<month<<" "<<day<<" "<<year<<endl;

    parseDate("12/1/2000", month, day, year);
    cout<<month<<" "<<day<<" "<<year<<endl;

    parseDate("1/1/2000", month, day, year);
    cout<<month<<" "<<day<<" "<<year<<endl;

    parseDate("    1/01/2000   ", month, day, year);
    cout<<month<<" "<<day<<" "<<year<<endl;
    return 0;
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
