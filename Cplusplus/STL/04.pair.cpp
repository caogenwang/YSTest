#include <iostream>
#include <list>
#include <algorithm>
using namespace std;

class Person
{
public:
    Person(string name,int age,int height){
        this->name = name;
        this->age = age;
        this->height = height;
    }
    ~Person(){
    }

    int age;
    string name;
    int height;
};


void test01()
{
    pair<string,int>p("Tom",20);
    cout<<p.first <<" "<<p.second<<endl;

    pair<string,int > p1 = make_pair("Jerry",24);
    cout<<p1.first <<" "<<p1.second<<endl;
    
}

int main()
{
    test01();
    return 0;
}
