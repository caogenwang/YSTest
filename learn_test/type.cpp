#include <iostream>
using namespace std;
class foo{
    public:
        foo(){}
        ~virtual foo(){}
    private:
        const int a;
        static int b;
        const static int c;
};
int foo::a = 0;
int foo::b=0;
const int foo::c=0;