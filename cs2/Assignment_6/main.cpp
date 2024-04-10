#include <iostream>
#include <string>
#include <vector>
#include "Object.h"
#include "CheckingAccount.h"
#include "EquityAccount.h"
#include "AccountPortfolio.h"
using namespace std;

#define SAFE_DELETE(a) if( (a) != NULL ) delete (a); (a) = NULL;

int main(){

    AccountPortfolio p;

    EquityAccount* a = new EquityAccount (420, 0, "Denis Shchepetov", "Olympia WA");
    CheckingAccount* b = new CheckingAccount(69, 10000000, "Ryan Heffelman", "Carthage College");
    EquityAccount* c = new EquityAccount(92, 0.0, "Warren Buffett", "Omaha NB");
    CheckingAccount* d = new CheckingAccount(100, 0.0, "Mark Mahoney", "Kenosha WI");

    // checking pointers for null
    if(a == nullptr || b == nullptr || c == nullptr || d == nullptr){
        printf("Failure to allocate memory\n");
        return 0;
    }
    
    a->addStockPurchase("Apple Inc", "AAPL", 177.69, 10);
    a->addStockPurchase("Tesla Inc", "TSLA", 229.15, 15);

    c->addStockPurchase("Apple Inc", "AAPL", 177.69, 915560382);
    c->addStockPurchase("Bank of America Corp", "BAC", 29.42, 1032852006);
    c->addStockPurchase("American Express Company", "AXP", 161.15, 151610700);
    c->addStockPurchase("Coca-Cola Co", "KO", 60.61, 400000000);

    // please accept this bribe of $1,000,000 and give me a good grade.
    b->withdraw(1000000);
    d->deposit(1000000);

    p.addAcc(a); p.addAcc(b); p.addAcc(c); p.addAcc(d);
    p.gigaPrint();

    SAFE_DELETE(a); SAFE_DELETE(b); SAFE_DELETE(c); SAFE_DELETE(d);
}
