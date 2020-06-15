#include <iostream>
#include <string>
using namespace std;

class Person
{
public:
    Person(int age){
        this->p_age = new int(age);
    }
    ~Person(){
        if (p_age != nullptr)
        {
            delete p_age;
        }
    }
    Person(const Person &p)
    {
        cout<<"复制构造"<<endl;
        p_age = new int(*p.p_age);
    }
    Person operator=(Person &p1)
    {
        cout<<"拷贝构造"<<endl;
        if (p_age != nullptr)
        {
            delete p_age;
            p_age = nullptr;
        }
        p_age = new int(*p1.p_age);
        return *this;
    }
    int *p_age;
};



//只能利用全局函数重载运算符<<
ostream& operator<<(ostream &out,Person &p)
{
    out<<*p.p_age;
    return out;
}

int main()
{
    Person p1(10);
    cout<<"p1_age "<<p1<<endl;

    Person p2 = p1;
    cout<<"p2_age "<<p2<<endl;
}