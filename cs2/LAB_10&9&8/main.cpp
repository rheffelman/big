#include <iostream>
#include <vector>
#include <string>

#include "Dictionary.h"

using namespace std;

int main(){
    Dictionary d("C:/Users/ryanh/Documents/CS2/LAB_10/LAB_10.2/bigDictionary.txt");
    string in;
    d.addMoreWords("C:/Users/ryanh/Documents/CS2/LAB_10/LAB_10.2/random_words.txt");

    printf("type stop to end the program.\n");
    for (in; in != "stop";){
        printf("\ntype in a word to search :)\n");
        getline(cin, in);
        
        if (in == "a word to search"){ 
            printf("\nsmartass\n");
            continue;
        }
        if (d.search(in)){
            printf("\n'%s' WAS found!\n", in.c_str());
        }
        else{
            printf("\nawkward... '%s' was NOT found.\n", in.c_str());
        }
    }
    return 0;
}