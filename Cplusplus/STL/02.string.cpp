#include <iostream>
#include <vector>
#include <algorithm>
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
//string是一个类
//1.构造函数
void test01()
{
    string s1;

    const char * str = "hello world";
    string s2(str);
    string s3(s2);
    string s4(10,'c');
}

//2.赋值操作




int main()
{   vector<int> v;
    v.push_back(1);
    v.push_back(1);
    v.push_back(1);
    v.push_back(1);
    v.push_back(1);
    cout<<sizeof(v)<<endl;
    cout<<v.capacity()<<endl;
    
    cout<<v.data()<<endl;
    return 0;
}