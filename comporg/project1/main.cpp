
#include <iostream>
int main(){
    struct Foo
    {
        int a;
        double b;
        float c;
        long d;
        short e;
    };
    std::cout << sizeof(Foo) << std::endl;
}