#include "single.h"
using namespace std;
int Single_test_main(int argc,const char **argv)
{
    s = Single::get_instance();
    cout<<s.a<<" "<<s.b<<endl;
}