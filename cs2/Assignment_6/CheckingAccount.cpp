#include "CheckingAccount.h"

void CheckingAccount::deposit(double x){
    m_d += x;
    transactions.push_back(x);
}
//--
void CheckingAccount::withdraw(double x){
    m_d -= x;
    transactions.push_back(x * -1);
}
//--
void CheckingAccount::printTransactionInfo() const{
    printf("Transaction History:\n");
    for (int i = 0; i < transactions.size(); i++){
        if (transactions[i] > 0) {
            printf("$+%.2f\n", transactions[i]);
        } else {
            printf("$%.2f\n", transactions[i]);
        }
    }
}
//--
void CheckingAccount::report() const{
    Object::report();
    printTransactionInfo();
    printf("\n");
}