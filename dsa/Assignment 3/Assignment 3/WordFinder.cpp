#include "WordFinder.h"

WordFinder::WordFinder(const string& dictionaryPath){
    d = new Dictionary(dictionaryPath);
}
//--
WordFinder::~WordFinder(){
    delete d;
}
//--
void WordFinder::makeWordsFromWord(const string& word){
    cout<<"Input String: "<<"\""<<word<<"\n"<<"Groups of Words: \n"<<endl;
    string cleansedWord = cleanse(word);
    vector < string > k;
    mwfwHelper(cleansedWord, 1, k);
    cout<<endl;
}
//--
void WordFinder::mwfwHelper(const string& word, int length, vector < string > k){
    string s = word.substr(0, length);

    if (d->isWordPresent(s)){
        if (length + 1 <= word.length()){
            k.push_back(s);
            mwfwHelper(word.substr(length, string::npos), 1, k);
        }
        else{
            k.push_back(s);
            printWords(k);
        }
        k.pop_back();
    }
    
    if (length + 1 <= word.length()) mwfwHelper(word, length + 1, k);
}
//--
void WordFinder::printWords(vector < string > k){
    for (int i = 0; i < k.size(); i++) cout<<k[i]<<" ";
    cout<<endl;
}
//--
string WordFinder::cleanse(const string& word){
    string retString = "";
    int x;
    int count = 0;

    for (int i = 0; i < word.size(); i++){
        x = int(word[i]);

        if ((x > 96) and (x < 123) or (x > 191) and (x < 256)){ 
            retString += char(x);
        }
        else if (x > 64 and x < 91){
            x += 32;
            retString += char(x);
        }
    }
    return retString;
}