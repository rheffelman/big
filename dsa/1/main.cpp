#include <iostream>
#include <string>
#include <istream>
using namespace std;

void copyAr(string* oldAr, string* newAr, int size);

int main(){
    int size = 5;
    string* allWords = new string[size] {"!"};
    int nextWordPosition = 0;
    string latestWord;
    cout << "Enter in some text and end with the word quit:";

    for (int i = 0; latestWord != "quit"; i++){
        cin >> latestWord;
        allWords[i] = latestWord;

        if (i == size - 1){
            size *= 2;
            string* newAr = new string[size];
            copyAr(allWords, newAr, size);
            delete[] allWords;
            allWords = newAr;
            delete[] newAr;
        }
    }
    for (int i = 0; i < size; i++){
        cout<<(i + 1)<<"."<<allWords[i]<<endl;
    }
    printf("exit\n");
}
//--
void copyAr(string* oldAr, string* newAr, int size){
    for (int i = 0; i < (size/2); i++){
        newAr[i] = oldAr[i];
    }
}