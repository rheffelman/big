#pragma once
#include <iostream>
#include "Object.h"
#include "EquityAccount.h"
#include "CheckingAccount.h"
using namespace std;

class AccountPortfolio{
public:
double portfolioValue() const;
void addAcc(Object* a);
void gigaPrint() const;
vector <Object*> accollection;
private:
};