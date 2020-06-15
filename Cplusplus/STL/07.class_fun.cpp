#include <iostream>

using namespace std;


//仿函数
class MyAdd{
public:
    int operator()(int a,int b)
    {
        return a + b;
    }
};


void test01()
{    

    MyAdd myadd;
    //1.像普通函数一样
    cout<< myadd(10,20) <<endl;;
}

//2.函数对象可以拥有自己的状态
class MyPrint{
public:
    MyPrint(){
        count = 0;
    }
    void operator()(string str)
    {
        cout<<str<<endl;
        count ++;
    }

    int count;
};

void test02()
{
    MyPrint myprint;
    myprint("Tom");
    myprint("Tom");
    myprint("Tom");
    myprint("Tom");
    cout<< myprint.count <<endl;

}

//3.函数对象作为参数传递
void doPrint(MyPrint &mp,string str)
{
    mp(str);
}

void test03()
{
     MyPrint myprint;
     doPrint(myprint,"Jack");
}

int main()
{
    test03();
    return 0;
}
