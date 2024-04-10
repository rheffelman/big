#include "Trie.h"

Trie::Trie(const string& filepath)
{
    ifstream infile;
    infile.open(filepath);
    string word;
    if (!infile.good()) cout<<"not good"<<endl;
    
    for (;infile.good();)
    {
        infile>>word;
        word = cleanse(word);
        if (word.length() >= 4)
        {
            insert(word, p_root, 0);
        }
    }
}
//--
Trie::~Trie()
{
    delete p_root;
}
//--
void Trie::insert(const string& elem, TrieElement* c, int elemIndex)
{
    if (elemIndex <= elem.length() - 1)
    {
        if (!c->subTries[int(elem[elemIndex]) - 97])
        {
            TrieElement* temp = new TrieElement(elem[elemIndex]);
            temp->wordSoFar = c->wordSoFar + elem[elemIndex];
            c->subTries[int(elem[elemIndex]) - 97] = temp;
            c = temp;
            if(elemIndex == elem.length() - 1)
            {
                c->isCompletedWord = true;
            }
            insert(elem, c, ++elemIndex);
            return;
        }
        else
        {
            c = c->subTries[int(elem[elemIndex]) - 97];
            insert(elem, c, ++elemIndex);
            return;
        }
    }
    return;
}
//--
string Trie::search(const string& word)
{
    return searchHelper(word, p_root, 0);
}
//--
string Trie::searchHelper(const string& word, TrieElement* c, int index)
{
    if (word == c->wordSoFar)
    {
        if (c->isCompletedWord)
        {
            return "FOUND";
        }
        return "PARTIAL";
    }
    if (index <= word.length() - 1)
    {
        if (c->subTries[int(word[index]) - 97])
        {
            return searchHelper(word, c->subTries[int(word[index]) - 97], index + 1);
        }
    }
    return "NOT FOUND";
}
//--
void Trie::printAllWords()
{
    printHelper(p_root);
}
//--
void Trie::printHelper(TrieElement* c)
{
    for (int i = 0; i < 26; ++i)
    {
        if (c->subTries[i])
        {
            if (c->subTries[i]->isCompletedWord)
            {
                cout<<c->subTries[i]->wordSoFar<<endl;
            }
            printHelper(c->subTries[i]);
        }
    }
    return;
}
//--
string Trie::cleanse(const string& word)
{
    string retString = "";
    int x;
    int count = 0;

    for (int i = 0; i < word.size(); i++)
    {
        x = int(word[i]);
        if ((x > 96) and (x < 123) or (x > 191) and (x < 256))
        { 
            retString += char(x);
        }
        else if (x > 64 and x < 91)
        {
            x += 32;
            retString += char(x);
        }
    }
    return retString;
}