#include <iostream>
#include <cmath>
#include <vector>
#include <string>
using namespace std;

int kthGrammar(int n, int k)
{
    vector < string > v;

    for (int i = 0; i < n; i++)
    {
        string x = "";
        if (i == 0) x += "0";
        else
        {
            for (int j = 0; j < v[i - 1].length(); j++)
            {
                if (v[i - 1][j] == '0') x += "01";
                else x += "10";
            }
        }
        v.push_back(x);
    }
    cout << ()
    return int(v[n - 1][k - 1]) - 48;
}

int main()
{
    int n = 5; int k = 5;
    int x = kthGrammar(n, k);
    cout << x;
}