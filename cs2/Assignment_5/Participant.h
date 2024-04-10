#pragma once
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Participant{
public:
    Participant(string n, string e, string p);
    string toString();
    void printAvailability();
    vector <int> availability;
    bool busyAr[7] {false};
    string name = "!!";
    string email = "!!";
    string phoneNumber = "!!";
private:
};