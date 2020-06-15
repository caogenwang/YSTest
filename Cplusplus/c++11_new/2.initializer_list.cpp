#include <iostream>
#include <vector>
using namespace std;

class P{
    public:
        P(int a,int b){
            cout<<"P:"<<a<<" "<<b<<endl;
        }
        P(std::initializer_list<int> val){
            cout<<"initializer_list:"<<endl;
            for (auto p = val.begin(); p !=  val.end(); p++)
            {
                cout<<*p<<endl;
            }
        }
        explicit P(int a,int b,int c)//不要隐士转换，防止类型转换
        {

        }  
};

int main()
{
    P a(2,3);
    P b{2,3};
    P r{777,5,42};
    P s={77,5};
    return 0;
}