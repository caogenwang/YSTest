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
    //类成员重载函数
    Person operator+(const Person &p1)
    {
        Person temp(0);
        temp.age =this->age + p1.age;
        return temp; 
    }

    int age;
};
//全局重载函数
Person operator+(Person &p1,Person &p2)
{
    Person temp(0);
    temp.age = p1.age + p2.age;
    return temp;
}

//函数重载
Person operator+(Person &p1,int num)
{
    Person temp(0);
    temp.age = p1.age + num;
    return temp;
}

int main()
{
    Person p1(10);
    cout<<"p1_age "<<p1.age<<endl;
    Person p2(20);
    cout<<"p2_age "<<p2.age<<endl;
    
    //类成员重载函数
    // Person p3 = p1 + p2;
    // Person p3 = p2.operator+(p1);

    //全局重载函数
    // Person p3 = p1 + p2;
    // Person p3 = operator+(p1,p2);

    //函数重载
    Person p3 = p2 + 10;
    cout<<"p3_age "<<p3.age<<endl;
}