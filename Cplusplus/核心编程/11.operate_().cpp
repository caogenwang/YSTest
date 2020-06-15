#include <iostream>
#include <string>
using namespace std;

class Person
{
public:
    Person(){
    }
    ~Person(){
    }

    int operator()(int num1,int num2)
    {
        return num1+num2;  
    }  

    // int age;
    // string name;
};



//只能利用全局函数重载运算符<<
ostream& operator<<(ostream &out,Person &p)
{
    // out<<p.name<<" "<<p.age;
    return out;
}


//仿函数
int main()
{
    cout<<Person()(10,20)<<endl;
}