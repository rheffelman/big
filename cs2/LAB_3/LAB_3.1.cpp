#include <iostream>
#include <vector>
using namespace std;

int main() {
    vector < int > die1Rolls;
    vector < int > die2Rolls;
    srand (time(0));

    int userIn;
    printf("How many rolls do you want?");
    cin >> userIn;

    for (int i = 0; i < userIn; i++){
        die1Rolls.push_back((rand() % 6) + 1);
        die2Rolls.push_back((rand() % 6) + 1);
    }
    
    for (int i = 0; i < die1Rolls.size(); i++){
        printf("%d) Die 1: %d Die 2: %d Sum: %d\n", i + 1, die1Rolls[i], die2Rolls[i], die1Rolls[i] + die2Rolls[i]);
    }
    return 0;
}
