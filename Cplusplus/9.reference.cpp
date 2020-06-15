#include <iostream>
#include <string>
using namespace std;

void swap(int &v1,int &v2)
{
    int temp = 0;
    temp = v1;
    v1 = v2;
    v2 = temp;
}

int main()
{
    double a = 1.2;
    double *p = &a;

    const double pi = 3.14;//指向常对象，序需要指向常对象的指针
    const double *pa;//指向常对象的指针，一般用作传递参数
    pa = &pi;


    pa = &a;//指向常对象的指针可以指向普通的对象，但是不能对对象进行修改
    // *pa = 5;

    //常指针
    int err = 0;
    int err2 = 1;
    int * const curPoint = &err;//常指针必须要初始化，同时不能再指向别的对象
    // curPoint = &err2;

    const double *const  pi_ptr = &pi;//指针不能指向其他的对象，也不能通过指针对对象进行修改。
}

//const 引用和普通的引用
// （1）在实际的程序中，引用主要被用做函数的形式参数--通常将类对象传递给一个函数.
// （2）一旦引用已经定义，它就不能再指向其他的对象.这就是为什么它要被初始化的原因.
// （3）const引用可以用不同类型的对象初始化(只要能从一种类型转换到另一种类型即可)，也可以是不可寻址的值，如文字常量。
// （4）不允许非const引用指向需要临时对象的对象或值，即，编译器产生临时变量的时候引用必须为const



