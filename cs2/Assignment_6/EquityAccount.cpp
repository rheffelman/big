#include "EquityAccount.h"

void EquityAccount::addStockPurchase(const string& name, const string& symbol, double pps, int numShares){
    Object * s = new Object(numShares, pps, name, symbol);
    purchases.push_back(s);
    m_d += pps * numShares;
}
//--
void EquityAccount::printStockInfo() const{
    for (int i = 0; i < purchases.size(); i++){
        printf("%d shares of %s (%s) at $%.2f per share.\n", purchases[i]->m_n, purchases[i]->m_strOne.c_str(), purchases[i]->m_strTwo.c_str(), purchases[i]->m_d);
    }
}
//--
void EquityAccount::report() const{
    Object::report();
    printStockInfo();
    printf("\n");
}