#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

void readFile(vector < string >& words, string filePath);
void print(const vector < vector < string > >& vec);

int main() {
    //holds all the words in a dictionary file
    vector<string> dictionaryWords;

    //fill the vector with words from a dictionary file
    readFile(dictionaryWords, "C:\\Users\\ryanh\\Documents\\CS2\\LAB_5\\LAB_5.1\\random_words.txt");

    vector<vector<string> > twoDVector;
    twoDVector.resize(26);
    for (int i = 0; i < dictionaryWords.size(); i++) {
        int index = (int(dictionaryWords[i][0]) - 97);
        twoDVector[index].push_back(dictionaryWords[i]);
    }
    print(twoDVector);
}
void print(const vector < vector < string > >& vec)
{
    cout << "Printing a 2D vector" << endl;
    for (int row = 0; row < vec.size(); row++)
    {
        for (int col = 0; col < vec[row].size(); col++)
        {
            cout << vec[row][col] << " ";
        }
        cout << endl;
    }
    cout << endl;
}
void readFile(vector < string >& words, string filePath)
{
    //create an input file stream variable
    ifstream infile;
    //attempt to open a file at a given path
    infile.open(filePath);

    //make sure the file was successfully opened
    if(infile.good())
    {
        //stores a word from the input file stream
        string latestWord;
        //while there are more words to read
        while(infile.good())
        {
            //read a word
            infile>>latestWord;
            //add it to the back of the vector
            words.push_back(latestWord);
        }
    }
    else //file not found, print an error
    {
        cout<<"Error opening the file: "<<filePath<<endl;
    }
}