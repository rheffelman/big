#pragma once
#include <vector>
#include <string>
#include <unordered_set>
#include <regex>
#include "Dictionary.h"

class WordleSolver
{

public:
    WordleSolver();
    unordered_set<string>* words;

    void subsetting(regex r);

private:

};