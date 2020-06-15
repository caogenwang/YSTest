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


void myprint(int val)
{
    cout<< val << endl;
}
//1. 遍历
void test01()
{
    vector<int> v;
    v.push_back(10);
    v.push_back(20);
    v.push_back(30);
    v.push_back(40);

    // vector<int>::iterator itBegin = v.begin();
    // vector<int>::iterator itEnd = v.end();
    // while (itBegin != itEnd)
    // {
    //     cout<< *itBegin << endl;
    //     itBegin ++;
    // }

    // for ( vector<int>::iterator it = v.begin();it != v.end(); it++)
    // {
    //     cout<< *it <<endl;
    // }

    //遍历算法
    for_each(v.begin(),v.end(),myprint);
    
}
//2. 内置数据结构
void test02()
{   

    vector<Person> v;

    Person p1(10,"Tom");
    Person p2(11,"Jack");
    Person p3(12,"Bery");
    Person p4(13,"Baker");

    v.push_back(p1);
    v.push_back(p2);
    v.push_back(p3);
    v.push_back(p4);

    for (vector<Person>::iterator it = v.begin();it != v.end();it ++)
    {
        cout<< "姓名："<< (*it).name << " 年龄:"<<(*it).age<<endl;
        cout<< "姓名："<< it->name << " 年龄:"<<it->age<<endl;
    }
    


}
//3.自定义数据结构
void test03()
{   

    vector<Person*> v;

    Person p1(10,"Tom");
    Person p2(11,"Jack");
    Person p3(12,"Bery");
    Person p4(13,"Baker");

    v.push_back(&p1);
    v.push_back(&p2);
    v.push_back(&p3);
    v.push_back(&p4);

    for (vector<Person*>::iterator it = v.begin();it != v.end();it ++)
    {
        Person*p=(*it);
        cout<< "姓名："<< (*it)->name << " 年龄:"<<(*it)->age<<endl;
        cout<< "姓名："<< p->name << " 年龄:"<<p->age<<endl;
    }
}

//4.容器嵌套容器

void test04()
{
    vector< vector<int> > v;
    
    //创建小容器
    vector<int> v1;
    vector<int> v2;
    vector<int> v3;
    vector<int> v4;

    for (int i = 0; i < 5; i++)
    {
        v1.push_back(i + 10);
        v2.push_back(i + 20);
        v3.push_back(i + 30);
        v4.push_back(i + 40);
    }
    

    v.push_back(v1);
    v.push_back(v2);
    v.push_back(v3);
    v.push_back(v4);

    for(vector<vector<int>>::iterator it = v.begin();it != v.end();it++)
    {
        for (vector<int>::iterator vit = (*it).begin(); vit  !=  (*it).end(); vit++)
        {
            cout<< *vit << " ";
        }
        cout<<endl;
    }
}

int main()
{   
    // test01();
    test04();
    return 0;
}