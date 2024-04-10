#include "WordleSolver.h"

WordleSolver::WordleSolver()
{
    string filePath = "A31_dictionary.txt";
    ifstream infile;
    infile.open(filePath);
    string word;

    for (;infile.good();)
    {
        infile >> word;
        if (word.length() == 5)
        {
            words->insert(word);
        }
    }
}
//--
void WordleSolver::subsetting(regex r)
{
    unordered_set<string>* temp = new unordered_set<string>;
    
}