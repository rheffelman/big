#include <iostream>
#include <vector>
#include <string>
#include <stdio.h>
#include <unordered_set>
#include <sstream>

#include "Dictionary.h"

using namespace std;

int main(){ 
    
    Dictionary d("./bigDictionary.txt");
    string testString = "projectial";
    fstream input(testString);
    printf("\n%s\n", testString.c_str());
    while(input.good()){
        string word;
        cin>>word;

        if (!d.search(word)){
            printf("\nsuggestions for mispelled word '%s': \n", word.c_str());
            vector < string > suggestions;
            d.getSuggestion(word, suggestions);
            printf("test1\n");
            for (auto suggestion : suggestions){
                printf("%s", suggestion.c_str());

                /*      prints the computed Levenshtein Distance and Jaccard Similarity Coefficient of each suggestion
                    to visualize how my algorithm works, hierarchically ranking words based on LD relative
                    to the mispelled word, then taking the words that are equivalent in LD and sorting and further
                    hierarchizing them based on JCS relative to the mispelled word.     */
                printf(" (LD: %d JCS: %.3f)\n", d.levenshteinDistance(word, suggestion), d.jaccardSimilarity(word, suggestion));
            }
        }
    }

    return 0;
}