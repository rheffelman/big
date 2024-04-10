#include <iostream>
#include <string>
#include "sqlite3.h"

using namespace std;

int main()
{
    sqlite3 *db;
    int statusOfOpen = sqlite3_open("/home/ryan/dbds/l13/a.sqlite", &db);

    if (statusOfOpen == SQLITE_OK)
    {
        cout << "Successfully opened the database" << endl;

        sqlite3_stmt* myStatement;
        int statusOfPrep = sqlite3_prepare_v2(db, "CREATE TABLE IF NOT EXISTS Students (ssn INTEGER PRIMARY KEY, first TEXT, last TEXT)", -1, &myStatement, NULL);

        if (statusOfPrep == SQLITE_OK)
        {
            int statusOfStep = sqlite3_step(myStatement);

            if (statusOfStep == SQLITE_DONE)
            {
                cout << "Successfully created the the Students table" << endl;
            }
            else
            {
                cout << "Problem creating the Students table" << endl;
            }

            sqlite3_finalize(myStatement);
        }
        else
        {
            cout << "Problem creating a prepared statement" << endl;
        }

        string first;
        string last;

        cout << "Enter in a first and last name: ";
        cin >> first;
        cin >> last;

        statusOfPrep = sqlite3_prepare_v2(db, "INSERT INTO Students (first, last) VALUES (?, ?)", -1, &myStatement, NULL);
        
        sqlite3_bind_text(myStatement, 1, first.c_str(), -1, SQLITE_STATIC);
        sqlite3_bind_text(myStatement, 2, last.c_str(), -1, SQLITE_STATIC);

        if (statusOfPrep == SQLITE_OK)
        {
            int statusOfStep = sqlite3_step(myStatement);

            if (statusOfStep == SQLITE_DONE)
            {
                cout << "Successfully inserted into the database" << endl;
            }
            else
            {
                cout << "Problem inserting into the database" << endl;
            }

            sqlite3_finalize(myStatement);
        }
        else
        {
            cout << "Problem creating a prepared statement" << endl;
        }

        statusOfPrep = sqlite3_prepare_v2(db, "SELECT * FROM Students", -1, &myStatement, NULL);

        if (statusOfPrep == SQLITE_OK)
        {
            int statusOfStep = sqlite3_step(myStatement);

            while (statusOfStep == SQLITE_ROW)
            {
                int id = sqlite3_column_int(myStatement, 0);
                first = (char*)sqlite3_column_text(myStatement, 1);
                last = (char*)sqlite3_column_text(myStatement, 2);

                cout << "Student Id: " << id << endl;
                cout << "First Name: " << first << endl;
                cout << "Last Name: " << last << endl;

                statusOfStep = sqlite3_step(myStatement);
            }

            sqlite3_finalize(myStatement);
        }
        else
        {
            cout << "Problem creating a prepared statement" << endl;
        }
    }
    else
    {
        cout << "Problem creating a prepared statement" << endl;
    }

    sqlite3_close(db);
    
    return 0;
}
