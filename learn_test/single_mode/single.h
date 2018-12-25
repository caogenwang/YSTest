#include <iostream>
using namespace std;
class Single
{
    public:
        Single get_instance();
        ~virtual Single();
        int value_get();
        int value_set(int a,int b);
    private:
        Single:a(0),b(0)();
        Single *single;
        int a;
        int b;
}