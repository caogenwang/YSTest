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

    // //前置++
    Person &operator++()
    {
        age++;
        return *this;
    }

    //后置++
    Person operator++(int)//int 占位参数，用于前置和后置
    {
        Person temp = *this;
        age++;
        return temp;
    }

    int age;
};



//只能利用全局函数重载运算符<<
ostream& operator<<(ostream &out,Person &p)
{
    out<<p.age;
    return out;
}

int main()
{
    Person p1(10);
    //前置递增
    // cout << ++ p1<< endl;

    //后置递增
    // cout << p1++ << endl;
    cout << p1 << endl;
}