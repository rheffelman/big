#include "Dictionary.h"

Dictionary::Dictionary(const string& dictionaryPath)
{
    ifstream infile;
    infile.open(dictionaryPath);

    if (infile.good())
    {
        string word;
        infile >> word;

        for (;infile.good();)
        {
            allWords.insert(word);
            infile >> word;
        }
    }
    else
    {
        cout << "Cannot open this file: " << dictionaryPath;
    }
}
//--
bool Dictionary::isWordPresent(const string& word)
{
    return allWords.count(word);
}