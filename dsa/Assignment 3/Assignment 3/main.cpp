#include "Dictionary.h"
#include "WordFinder.h"
#include <iostream>
#include <string>
using namespace std;

int main()
{
    string path = "bigDictionary.txt";
    WordFinder finder(path);

    finder.makeWordsFromWord("carton");
    finder.makeWordsFromWord("Carton");
    finder.makeWordsFromWord("car ton");
    finder.makeWordsFromWord("cart On");
    finder.makeWordsFromWord("sodapop");
    finder.makeWordsFromWord("ihaveafriendwhosenameisjane");
    finder.makeWordsFromWord("abcxyz");
    finder.makeWordsFromWord("Ihaveasodapop");
    finder.makeWordsFromWord("washingtonisinabuilding"); //doesnt work because "building" isnt in file.
    finder.makeWordsFromWord("cartomynameisxyz");
    
    cout<<"exited";
}
