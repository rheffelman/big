#pragma once
#include <string>
#include <vector>
#include <iostream>
using namespace std;
template < typename T >
class HashTable
{
public:

    HashTable();
    HashTable(int initSize);
    ~HashTable();
    void insert(const string& key, const T& value);
    bool retrieve(const string& key, T& value);
    bool isEmpty();
    int size();

private:

    struct KeyValuePair
    {
        string key;
        T value;
    };
    vector < vector < KeyValuePair* > > table;
    int numElements;
    int sizeOfTable;

    int hash(const string& key);
    bool isPrime(int primeCandidate);
    int findNextPrime(int primeCandidate);
};
//--
template < class T >
HashTable<T>::HashTable()
{
    numElements = 0;
    sizeOfTable = 101;
    table.resize(sizeOfTable);
}
//--
template < class T >
HashTable<T>::HashTable(int initSize)
{
    numElements = 0;
    int x = initSize * 2;

    if (isPrime(x))
    {
        table.resize(x);
        sizeOfTable = x;
    }
    else
    {
        table.resize(findNextPrime(x));
        sizeOfTable = findNextPrime(x);
    }
}
//--
template < class T >
HashTable<T>::~HashTable()
{
    for (int i = 0; i < table.size(); i++)
    {
        for (int j = 0; j < table[i].size(); j++)
        {
            delete table[i][j];
        }
    }
}
//--
template < class T >
void HashTable<T>::insert(const string& key, const T& value)
{
    KeyValuePair* newKV = new KeyValuePair;
    newKV->key = key;
    newKV->value = value;

    int insertPos = hash(key);
    table[insertPos].push_back(newKV);

    numElements++;
}
//--
template < class T >
bool HashTable<T>::retrieve(const string& key, T& value)
{
    int retrievePos = hash(key);
    bool retVal = false;

    for (int i = 0; i < table[retrievePos].size(); i++)
    {
        if (key == table[retrievePos][i]->key)
        {
            value = table[retrievePos][i]->value;
            retVal = true;
            break;
        }
    }
    return retVal;
}
//--
template < class T >
bool HashTable<T>::isEmpty()
{
    return size() == 0;
}
//--
template < class T >
int HashTable<T>::size()
{
    return numElements;
}
//--
template < class T >
bool HashTable<T>::isPrime(int primeCandidate)
{
    if (primeCandidate <= 1) return false;
    if (primeCandidate <= 3) return true;
    if (primeCandidate % 2 == 0 or primeCandidate % 3 == 0) return false;

    for (int i = 0; i <= primeCandidate; i += 6)
    {
        if (primeCandidate % i == 0 or num % (i + 2) == 0) return false;
    }
    return true;
}
//--
template < class T >
int HashTable<T>::findNextPrime(int primeCandidate)
{
    if (primeCandidate <= 1) return 2;
    int next = primeCandidate + 1;

    for (;true; next++)
    {
        if (isPrime(next)) return next;
    }
}
//--
template < class T >
int HashTable<T>::hash(const string& key)
{
    unsigned int x = 1;
    
    for (int i = 0; i < key.length(); i++)
    {
        x *= 33;
        x += int(key[i]);
    }
    return x % sizeOfTable;
}
// template < class T >
// int HashTable<T>::hash(const string& key)
// {
//     int hashedPosition;
//     int firstLetter = tolower(key[0]);
//     if (firstLetter >= 'a' and firstLetter <= 'z')
//     {
//         hashedPosition = firstLetter - 'a';
//     }
//     else
//     {
//         hashedPosition = 26;
//     }
//     return hashedPosition;
// }

/*
-insert
    O(1) approximately on average.

-retrieve
    O(1) approximately on average.

-remove
    O(1) approximately on average.

Mod division by a prime number?

Hash function:
    Key % prime#
    prime# = same size as the array
*/