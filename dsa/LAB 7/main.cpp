#include <iostream>
#include <string>
using namespace std;

void countDown(int x)
{
    if (x >= 0)
    {
        printf("%d\n", x); // prints the value of x (and a linebreak)
        countDown(x - 1); // recurses with x = x - 1
    }
    else return;
}

void countUp(int x)
{
    if (x >= 0)
    {
        countUp(x - 1); // recurses with x = x - 1
        printf("%d\n", x); // prints the value of x (and a linebreak)
    }
    else return;
}

int main()
{
    int x = 10;
    countDown(x);
}
