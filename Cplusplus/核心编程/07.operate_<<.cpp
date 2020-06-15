#include <iostream>
#include <string>
using namespace std;

class Person
{
public:
    Person(int age){
        this->age = age;
    }
    ~Person(){}
    int age;
};

//只能利用全局函数重载运算符<<
ostream& operator<<(ostream &cout,Person &p)
{
    cout<<p.age;
    return cout;
}


int main()
{
    Person p1(10);
    cout<< p1<<endl<<"hello world"<<endl;
}