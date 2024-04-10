#pragma once
#include "Object.h"

class EquityAccount : public Object{
public:
    EquityAccount(int accNumber, double accBalance, const string& name, const string& address) : Object(accNumber, accBalance, name, address){}
    void report() const override;
    void addStockPurchase(const string& name, const string& symbol, double pps, int numShares);
    vector <Object*> purchases;
    void printStockInfo() const;
private:
};