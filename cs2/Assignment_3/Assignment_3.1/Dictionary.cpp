#include "Dictionary.h"

Dictionary::Dictionary(const string& dictionaryPath){
    words.resize(260);
    ifstream infile;
    infile.open(dictionaryPath);

    if (infile.good()){
        string word;
        infile >> word;

        for (; infile.good();){
            word = cleanse(word);
            words[getWordPos(word)].push_back(word);
            infile >> word;
        }
    }
    else{
        printf("Cannot open this file: %s", dictionaryPath.c_str());
    }
}
//--
void Dictionary::getSuggestion(const string& word, vector < string >& suggestions){
    const int maxDistance = 4;
    vector < vector < string > > lev(maxDistance);
    for (int i = 0; i < words.size(); i++){
        for (int j = 0; j < words[i].size();j++){
            int distance = levenshteinDistance(word, words[i][j]);
            if (distance < maxDistance) lev[distance].push_back(words[i][j]);
        }
    }

    for (int i = 1; i < lev.size() - 1; i++){
        bubbleSortByJaccard(lev[i], word);
    }
    int count = 0;
    for (int i = 1; i < lev.size(); i++){
        if (count >= 10) break;
        for (int j = 0; j < lev[i].size(); j++){
            suggestions.push_back(lev[i][j]);
            count++;
            if (count >= 10) break;
        }
    }
}
//--
double Dictionary::jaccardSimilarity(const string& word1, const string& word2){

    /*  checks word2 for each character in word1, if it finds a common
    character it inserts it in the set, creating the intersection of the 2 words(sets).  */
    unordered_set < char > intersection;
    for (int i = 0; i < word1.size(); i++) {
        if (word2.find(word1[i]) != string::npos){
            intersection.insert(word1[i]);
        }
    }

    /*  iterates through and inserts all characters from the first word, then all characters 
    from the second word in order to get the union of the sets. Can't call my set "union" unfortunately :(  */
    unordered_set < char > unionSet;
    for (int i = 0; i < word1.size() + word2.size(); i++) {
        if (i < word1.size()) {
            unionSet.insert(word1[i]);
        }
        else {
            unionSet.insert(word2[i - (word1.size())]);
        }
    }

    /*  Jaccard Similarity Coefficient of sets A and B = the cardinality of the intersection of A and B divided by the
    cardinality of the union of Sets A and B, which is what we've just calculated and are about to return.  */
    return static_cast<double>(intersection.size()) / static_cast<double>(unionSet.size());
}
//--
void Dictionary::bubbleSortByJaccard(vector <string>& vec, const string& word) {
    for (;;){
        bool swapMade = false;
        for (int i = 0; i < vec.size() - 1; i++) {
            double val1 = jaccardSimilarity(word, vec[i]);
            double val2 = jaccardSimilarity(word, vec[i + 1]);
            if (val2 > val1){
                swap(vec[i], vec[i + 1]);
                swapMade = true;
            }
        }
        if (!swapMade) break;
    }
}
//--
int Dictionary::levenshteinDistance(const string& word1, const string& word2) {
    int rows = word1.length();
    int columns = word2.length();

    //  initializes 2d vector(matrix) with dimensions equal to word1.length() + 1 by word2.length() + 1. sets each value as 0 to start with.
    vector < vector<int> > matrix(rows + 1, vector <int> (columns + 1, 0));

    //  iterates through the first row assigning i to each index (starting at [1]) which keeps incrementing, so it looks like 0, 1, 2, 3... word1.length() + 1
    for (int i = 1; i <= rows; i++) matrix[i][0] = i;

    //  same thing but for the first column
    for (int i = 1; i <= columns; i++) matrix[0][i] = i;

    //  iterates through the 2d vector, starting at index 1 because matrix[0][0] is always 0.
    for (int i = 1; i <= rows; i++) {
        for (int j = 1; j <= columns; j++) {
            
            //  checks equivalence of each character in word1 to each character in word2, can do this with our loop setup because our matrix is created based on our words' sizes.
            if (word1[i - 1] == word2[j - 1]) {

                //  if they're indeed equivalent, assigns matrix[i][j] with matrix[i - 1][j - 1], so the previous value, essentially leaving it unchanged.
                matrix[i][j] = matrix[i - 1][j - 1];
            } 

            else {

                //  executes the minimum of the 3 levenshtein operations and adds 1 incrementing the distance.
                //  matrix[i - 1][j] representing insertion, matrix[i][j - 1] representing deletion, matrix[i - 1][j - 1] representing substitution
                matrix[i][j] = 1 + min({matrix[i - 1][j], matrix[i][j - 1], matrix[i - 1][j - 1]});
            }
        }
    }
    
    return matrix[rows][columns];
}
//--
void Dictionary::addMoreWords(const string& filePath) {
    ifstream infile;
    infile.open(filePath);

    if (infile.good()) {
        vector <int> indices;
        string word;
        infile >> word;

        for (int i = 0; infile.good();) {                    
            word = cleanse(word);
            bool existsInIndices = false;
            for (int j = 0; j < indices.size(); j++) {
                if (indices[j] == getWordPos(word)) {
                    existsInIndices = true;
                }
            }
            if (existsInIndices == false) {
                indices.push_back(getWordPos(word));
            }
            words[getWordPos(word)].push_back(word);
            infile >> word;                                            
        }
        for (int i = 0; i < indices.size(); i++) {
            sort(words[indices[i]].begin(), words[indices[i]].end());
        }
    }
    
}
//--
int Dictionary::getWordPos(string& word) {
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
//--
bool Dictionary::search(string& searchWord) {
    searchWord = cleanse(searchWord);
    int index = getWordPos(searchWord);
    int end = words[index].size() - 1;
    int start = 0;
    int middle;

    for (int i = 0; start <= end; i++) {
        middle = (start + end) / 2;

        if (searchWord == words[index][middle]) {
            return true;
        }
        else if (searchWord < words[index][middle]) {
            end = middle - 1;
        }
        else{
            start = middle + 1;
        }
    }

    return false;
}
//--
string Dictionary::cleanse(const string& word)
{
    string retString = "";
    int x;
    int count = 0;

    for (int i = 0; i < word.size(); i++) {
        x = int(word[i]);

        if ((x > 96) and (x < 123) or (x > 191) and (x < 256)) { //if it's a lowercase letter or utf8 character, add it to the return string.
            retString += char(x);
        }
        else if (x > 64 and x < 91) { //if it's an uppercase letter, convert to it's lowercase equivalent, and add it to the return string.
            x += 32;
            retString += char(x);
        }
    }
    return retString;
}