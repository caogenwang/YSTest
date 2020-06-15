#include <iostream>
#include <vector>
using namespace std;

// 递归打印,必须要加的
void func()
{

}

template<typename... Args>
void func(const Args& ...args)
{
    cout<<sizeof...(args)<<endl;
    func(args...);
}

template<typename T,typename... Args>
void func(const T&FirstArg,const Args& ...args)
{
    cout<<FirstArg<<endl;
    func(args...);
}

//重写printf
/*
test:
int *pi = new int;
print("%d %s %p %lf\n",15,"this is Aee",pi,3.14159253);
*/
void print(const char *s)
{
    while(*s)
    {
        if(*s=='%' && *(++s) != '%')
            throw std::runtime_error("invalid format string");
        std::cout<<*s++;
    }
}
template<typename T,typename...Args>
void print(const char *s,T value,Args...args)
{
    while (*s)
    {
        if(*s=='%' && *(++s) != '%'){
            std::cout<<value;
            print(++s,args...);
            return;
        }
        std::cout<<*s++;
    }
    throw std::logic_error("extra arguments provided to pointer");
}

//若是参数类型都相同，可以使用initializer_list
/*
test:
cout<<max({1,2,3,4,5,6})<<endl;
*/
/*
cout<<maximunm(57,48,60,100,20,18)<<endl;
*/
int maximum(int n)
{
    return n;
}
template<typename... Args>
int maximum(int n,Args...args)
{
    return std::max(n,maximum(args...));
}

//eg:5
// template<int MAX,typename... Args>
// struct PRINT_TUPLE<MAX,MAX,Args...>{
//     static void print(std::ostream &os,const tuple<Args...>&t){
//     }
// };

// template<int IDX,int MAX,typename... Args>
// struct PRINT_TUPLE{
//     static void print(ostream &os,const tuple<Args...>&t){
//         os<<std::get<IDX> (t)<<(IDX+1==MAX?"":",");
//     }
//     PRINT_TUPLE<IDX+1,MAX,Args...>::print(os,t);
// };

// template<typename... Args>
// ostream& operator<<(ostream&os,const tuple<Args...>&t)
// {
//     os<<"[";
//     PRINT_TUPLE<0,sizeof...(Args),Args...>::print(os,t);
//     return os<<']';
// }

//eg6:
// template<typename...Values>
// class tuple{};

template<> class tuple<>{};

template<typename Head,typename...Tail>
class tuple<Head,Tail...>:private tuple<Tail...>
{

};

int main()
{
    return 0;
}