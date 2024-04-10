#include "AccountPortfolio.h"
#include "assert.h"

void AccountPortfolio::gigaPrint() const{
    printf("Total Portfolio Value: $%.2f\n\n", portfolioValue());
    
    for (int i = 0; i < accollection.size(); i++){
        accollection[i]->report();
    }
}
//--
double AccountPortfolio::portfolioValue() const{
    double retVal = 0;
    
    for (int i = 0; i < accollection.size(); i++){
        assert(accollection[i]);
        retVal += accollection[i]->m_d;
    }
    
    return retVal;
}
//--
void AccountPortfolio::addAcc(Object* a){
    if(a == nullptr){
        printf("Invalid argument, a == nullptr");
        return;
    }
    
    accollection.push_back(a);
}