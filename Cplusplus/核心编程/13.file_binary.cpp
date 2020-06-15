#include <iostream>
#include <string>
#include <fstream>
using namespace std;

class Person
{
public:

    char name[64];
    int age;
};

int main()
{
    fstream ofs;
    ofs.open("Person.txt",ios::out|ios::binary);
    Person p = {"张三",18};
    ofs.write((const char*)&p,sizeof(Person));


    fstream ifs("Person.txt",ios::in|ios::binary);
    if(ifs.is_open())
    {
        Person pp;
        ifs.read((char*)&p,sizeof(Person));
        cout<<p.age<<" "<<p.name<<endl;
    }
    else
    {
        return 0;
    }
    

    return 0;
}