#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <algorithm>

#include "Dictionary.h"
 
 Dictionary::Dictionary(const string& dictionaryPath){
    words.resize(260);

    ifstream infile;
    infile.open(dictionaryPath);

    if (infile.good()){
        string word;
        infile >> word;

        for (int i = 0; infile.good(); i++){
            word = cleanse(word);
            words[getWordPos(word)].push_back(word);
            infile >> word;
        }
    }
    else{
        printf("Cannot open this file: %s", dictionaryPath.c_str());
    }
}

void Dictionary::addMoreWords(const string& filePath){
    ifstream infile;
    infile.open(filePath);

    if (infile.good()){
        vector < int > indices;
        string word;
        infile >> word;

        for (int i = 0; infile.good();){                    
            word = cleanse(word);
            bool existsInIndices = false;
            for (int j = 0; j < indices.size(); j++){
                if (indices[j] == getWordPos(word)){
                    existsInIndices = true;
                }
            }
            if (existsInIndices == false){
                indices.push_back(getWordPos(word));
            }
            words[getWordPos(word)].push_back(word);
            infile >> word;                                            
        }
        for (int i = 0; i < indices.size(); i++){
            sort(words[indices[i]].begin(), words[indices[i]].end());
        }
    }
    
}

int Dictionary::getWordPos(string& word){
    word = cleanse(word);
    int charIndex = (int(word[0]) - 97);
    int wordLengthIndex;
    
    if (word.size() > 10) {
        wordLengthIndex = 9;
    }
    else{
       wordLengthIndex = word.size() - 1;
    }
    
    return stoi(to_string(charIndex) + to_string(wordLengthIndex));
}

void Dictionary::print(){
    for (int i = 0; i < words.size(); i++){
        for (int j = 0; j < words[i].size(); j++){
            printf("%s ", words[i][j].c_str());
        }
        printf("\n\n");
    }
}

bool Dictionary::search(string& searchWord){
    searchWord = cleanse(searchWord);
    int index = getWordPos(searchWord);
    int end = words[index].size() - 1;
    int start = 0;
    int middle;

    for (int i = 0; start <= end; i++){
        middle = (start + end) / 2;

        if (searchWord == words[index][middle]){
            return true;
        }
        else if (searchWord < words[index][middle]){
            end = middle - 1;
        }
        else{
            start = middle + 1;
        }
    }

    return false;
}

string Dictionary::cleanse(const string& word){
    string retString = "";
    int x;
    int count = 0;

    for (int i = 0; i < word.size(); i++){
        x = int(word[i]);

        if ((x > 96) and (x < 123)){
            retString += char(x);
        }
        else if (x > 64 and x < 91){
            x += 32;
            retString += char(x);
        }
        else if (count == 0){
            printf("\nbtw there's a weird character in your word\n");
            count++;
        }
    }
    return retString;
}