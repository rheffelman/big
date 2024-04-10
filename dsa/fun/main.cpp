#include <iostream>
#include <string>
#include <vector>
#include <regex>
#include <fstream>
using namespace std;
int main()
{   

    string pyramid = "";

    for (int i = 0; i < 5; i++)
    {
        pyramid += "*";
        cout<<pyramid<<endl;
    }
    cout<<"Finito";
}
