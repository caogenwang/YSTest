#include <iostream>
#include <string>
using namespace std;

class Person
{
public:
    Person(int age,string name){
        this->age = age;
        this->name = name;
    }
    ~Person(){
    }

    bool operator==(const Person &p1)
    {
        if (age == p1.age && name == p1.name)
        {
            return true;
        }
        return false;
    }

    bool operator!=(const Person &p1)
    {
        if (age != p1.age || name != p1.name)
        {
            return true;
        }
        return false;
    }
   
    int age;
    string name;
};



//只能利用全局函数重载运算符<<
ostream& operator<<(ostream &out,Person &p)
{
    out<<p.name<<" "<<p.age;
    return out;
}

int main()
{
    Person p1(10,"Tom");
    Person p2(10,"Jack");
    if (p1 == p2 )
    {
        cout<<"p1 和 p2是相等的"<<endl;
    }
    else
    {
        cout<<"p1 和 p2是不相等的"<<endl;
    }

    if (p1 != p2 )
    {
        cout<<"p1 和 p2是不相等的"<<endl;
    }
    else
    {
        cout<<"p1 和 p2是相等的"<<endl;
    }
}