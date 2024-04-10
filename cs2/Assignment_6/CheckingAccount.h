#pragma once
#include "Object.h"

class CheckingAccount : public Object{
public:
CheckingAccount(int accNumber, double accBalance, const string& name, const string& address) : Object(accNumber, accBalance, name, address){}
void report() const override;
void printTransactionInfo() const;
void deposit(double x);
void withdraw(double x);
vector <double> transactions;
private:
};