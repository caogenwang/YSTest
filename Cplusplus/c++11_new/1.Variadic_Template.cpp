#include <iostream>
#include <bitset>
#include <vector>
using namespace std;
// 递归打印
void print()
{

}


template<typename T,typename...Args>
void print(const Args&... args)
{
    cout<<sizeof...(args)<<endl;
}

template<typename T,typename...Args>
void print(const T& firstArg,const Args&... args)
{
    cout<<firstArg<<endl;
    cout<<"size:"<<sizeof...(args)<<endl;
    print(args...);//注意不要忘了这个点点点
}
//eg:
// class CustmerHash{
//     public:
//         std::size_t operator()(const CustmerHash &c) const
//         {
//             // return hash_val(c.fname,c.lname,c.no);
//         }
//     private:
//         std::string fname;
//         std::string lname;
//         std::size_t no;
// };

//initializer_list
void print(std::initializer_list<int> val)
{
    for (auto p = val.begin(); p !=  val.end(); p++)
    {
        cout<<*p<<endl;
    }
}



int main()
{
    // vector<int>v{2,3,4,5};
    // int j{};
    // int *p{};
    // cout<<j<<endl;
    // cout<<p<<endl;
    // print(7.5,"hello",'0',42);

    print({2,3,4,5});
    return 0;
}