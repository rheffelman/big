#include <iostream>
using std::cout;
using std::endl;

extern "C" long fact(long);

int main(int argc, char ** argv){
    cout << "fact(5) is: " <<  fact(5) << endl;
    return 0;
}