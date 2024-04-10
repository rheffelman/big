#include "CrosswordHelper.h"

CrossWordHelper::CrossWordHelper(const string& filePath, int wordLength){
    words.resize(wordLength);
    for (int i = 0; i < words.size(); i++){
        words[i].resize(26);
    }
    ifstream infile;
    infile.open(filePath);
    string word;

    for (;infile.good();){
        infile >> word;

        for (int i = 0; i < wordLength; i++){
            if (word.length() == wordLength){
                assert (tolower(word[i]) >- 97 and tolower(word[i]) <= 97 + 26);
                words[i][int(tolower(word[i])) - 97].push_back(word);
            }
        }
    }
}
//--
void CrossWordHelper::getSuggestions(const string& word, IntersectionContainer < string >& c){
    if (word.length() == words.size()){
        for (int i = 0; i < word.length(); i++){
            if (word[i] != '-'){
                c.add(words[i][int(word[i]) - 97]);
            }
        }
    }
}
//--
