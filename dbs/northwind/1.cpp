#include <iostream>
#include <string>
#include "sqlite3.h"
using namespace std;

int main(){
    sqlite3 *db;
    int statusOfOpen = sqlite3_open("home/ryan/northwind/NorthwindLimited.sqlite", &db);
    
    if (statusOfOpen == SQLITE_OK){
        cout << "Successfully opened the database\n";
    }
}