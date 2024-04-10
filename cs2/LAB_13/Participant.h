#include <iostream>
#include <string>

using namespace std;

class Participant{
public:
    Participant(string n, string e, string p);
    string toString();
private:
    string name = "!!";
    string email = "!!";
    string phoneNumber = "!!";
};