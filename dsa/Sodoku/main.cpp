#include <iostream>
#include <string>
#include <vector>
#include <fstream>
using namespace std;

bool yellowCheck(string word, string yellow);
bool greenCheck(string word, string green);
bool greyCheck(string word, string grey);
bool look(string word, char c);
void readIn(vector < string >& v, int wordLength);
//--
int main(){
    vector < string > allWords;
    vector < string > viableWords;
    readIn(allWords, 5);
    
    for (int i = 0; i < allWords.size(); i++){
        if (look(allWords[i], 't') and look(allWords[i], 'r') and look(allWords[i], 'e')){
            if (allWords[i][1] != 't' and allWords[i][3] != 'r' and allWords[i][4] != 'e'){
                if (!look(allWords[i], 's') and !look(allWords[i], 'e')){
                    printf("%s\n", allWords[i].c_str());
                }

            }
        }
    }
}
//--
// bool yellowCheck(string word, string yellow){
//     for (int i = 0; i < word.length(); i++){
//         for (int j = 0; j < yellow.length(); j++){
            
//         }
//     }
// }
//--
// bool greenCheck(string word, string green){
//     for (int i = 0; i < green.length(); i++){
//         if (green[i] != '-'){
//             if (word[i] != green[i]) return false;
//         }
//     }
//     return true;
// }
// //--
// bool greyCheck(string word, string grey){
//     for (int i = 0; i < word.length(); i++){
//         for (int j = 0; j < grey.length(); j++){
//             if (word[i] == grey[j]) return false;
//         }
//     }
//     return true;
// }
//--
bool look(string word, char c){
    for (int i = 0; i < word.length(); i++){
        if (word[i] == c) return true;
    }
    return false;
}
//--
void readIn(vector < string >& v, int wordLength){
    //opens an ifstream infile at a specified filepath (probably want to pass in from main)
    string filePath = "C:\\Users\\ryanh\\OneDrive\\Documents\\GitHub\\CSC-2560\\Assignment 1\\bigDictionary.txt";
    ifstream infile;
    infile.open(filePath);

    //infile.good() or loop condition returns false if End-Of-File is reached on input operation
    for (;infile.good();){
        string word;
        infile >> word; //reads in a word from the file just like cin
        if (word.length() == wordLength){
            v.push_back(word);
        }
    }
}