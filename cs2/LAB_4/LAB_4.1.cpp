#include <iostream>
#include <vector>
#include <assert.h>
using namespace std;

void printGrades(const vector < float >& theGrades);
float vectorAverage(const vector < float >& theGrades);
float otherVectorAverage(const vector < float >& theGrades);

int main() {
    vector < float > grades = {17, 5, 22, 9, 14, 6, 12, 3, 19, 8};

    printf("average of grades: %.3f\n", vectorAverage(grades));
    printf("average of grades with min/max removed: %.3f", otherVectorAverage(grades));
    return 0;
}
float otherVectorAverage(const vector < float >& theGrades){
    if (theGrades.size() <= 2){
        printf("\nwarning! your vector size is <= 2, so taking an average with the min/max removed is equivalent to taking an average of no elements.\n\n");
        return 0;
    }
    float greatest = theGrades[0];
    float least = theGrades[0];
    float sum = 0;
    for (int i = 0; i < theGrades.size(); i++){
        sum += theGrades[i];
        if (theGrades[i] > greatest){
            greatest = theGrades[i];
        }
        else if (theGrades[i] < least){
            least = theGrades[i];
        }
    }
    return (sum - (greatest + least)) / (theGrades.size() - 2);
}
float vectorAverage(const vector < float >& theGrades){
    float sum;
    for (int i = 0; i < theGrades.size(); i++){
        sum += theGrades[i];
    }
    return sum / theGrades.size();
}
void printGrades(const vector < float >& theGrades)
{
    for (int i = 0; i < theGrades.size(); i++)
    {
        cout << "Grade " << (i + 1) << ": " << theGrades[i] << endl;
    }
}