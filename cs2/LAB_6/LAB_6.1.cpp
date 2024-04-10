#include <iostream>
#include <string>
#include <vector>
#include <ctime>
using namespace std;
struct Roll
{
    //holds a certain number of 6-sided die rolls (1-6)
    vector < int > dieRolls;

    //the sum of all the die rolls
    int sum;
};

struct RollCollection
{
    //the number of dice being rolled
    int numDicePerRoll;

    //all of the dice rolls
    vector < Roll > allRolls;

    //the number of times that each sum occurred
    vector < int > frequencies;
};
void getRolls(Roll& aRoll, int numDice);
void fillDieRolls(RollCollection& collection, int numRolls, int numDice);
void fillFrequencies(RollCollection& dieFrequencies);
void displayResults(const RollCollection& dieFrequencies);

int main()
{
    srand(time(0));

    //create an object to holds rolls and frequencies
    RollCollection test1;

    //create 10 rolls of 5 dice
    fillDieRolls(test1, 10, 5);
    fillFrequencies(test1);

    //display all of the rolls and the frequencies
    displayResults(test1);

    return 0;
}

//generates a roll of numDice dice
void getRolls(Roll& aRoll, int numDice){
    int sum = 0;
    for (int i = 0; i < numDice; i++){
        int randNum = (rand() % 6) + 1;
        sum += randNum;
        aRoll.dieRolls.push_back(randNum);
    }
    aRoll.sum = sum;
}

//stores numRolls rolls of numDice dice
void fillDieRolls(RollCollection& collection, int numRolls, int numDice){
    for (int i = 0; i < numRolls; i++){
        Roll temp;
        getRolls(temp, numDice);
        collection.allRolls.push_back(temp);
    }
    collection.numDicePerRoll = numDice;
}

//fills the frequencies of all the sums of all of the rolls
void fillFrequencies(RollCollection& dieFrequencies){
    //creates 6 * numDicePerRoll(which should be the maximum amount of a sum) slots in our frequencies vector.
    dieFrequencies.frequencies.resize(6 * dieFrequencies.numDicePerRoll, 0);
    //tallys up each time a sum is seen in the corresponding index in the frequencies vector.
    for (int i = 0; i < dieFrequencies.allRolls.size(); i++){
        dieFrequencies.frequencies[dieFrequencies.allRolls[i].sum]++;
    }
}

//displays all of the rolls and the frequency of each possible sum
void displayResults(const RollCollection& dieFrequencies){
    //outputs roll vectors
    for (int i = 0; i < dieFrequencies.allRolls.size(); i++){
        printf("Rolls: ");
        for (int i2 = 0; i2 < dieFrequencies.allRolls[i].dieRolls.size(); i2++){
            printf("%d ", dieFrequencies.allRolls[i].dieRolls[i2]);
        }
        printf("-- sum %d\n", dieFrequencies.allRolls[i].sum);
    }
    //outputs sum frequencies
    for (int i = 0; i < dieFrequencies.frequencies.size(); i++){
        if (dieFrequencies.frequencies[i] != 0){
            printf("%d: %d\n", i, dieFrequencies.frequencies[i]);
        }
    }
}