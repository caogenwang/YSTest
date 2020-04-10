#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <string>
using namespace std;
//1.
// template<class T>
// class CMutiply{
//     public:
//     T operator()(const T &ele1,const T &ele2){
//         return ele1 * ele2;
//     }
// };

// int main()
// {
//     vector<int>a,b;
//     for (int i = 0; i < 10; i++)
//         a.push_back(i);
//     for (int i = 0; i < 10; i++)
//         b.push_back(i);
    
//     vector<int> res(10,0);
//     transform(a.begin(),a.end(),b.begin(),res.begin(),CMutiply<int>());
    
//     for (int i = 0; i < res.size(); i++)
//         cout<<res[i]<<endl;
//     return 0;
// }


// class CCompare{
//     public:
//     bool operator()(const string &str1,const string &str2) const
//     {
//         string str1LoweCase;
//         str1LoweCase.resize(str1.size());
//         transform(str1.begin(),str1.end(),str1LoweCase.begin(),tolower());

//         string str2LoweCase;
//         str2LoweCase.resize(str2.size());
//         transform(str2.begin(),str2.end(),str2LoweCase.begin(),tolower());
//     }
// };

// int main()
// {
//     set<string> name;
//     name.insert("A");
//     name.insert("B");
//     name.insert("C");
//     name.insert("D");
//     name.insert("C");
//     set<string>::iterator it = name.find("C");
//     if (it != name.end())
//     {
//         cout<<"find"<<endl;
//     }
//     else
//     {
//         cout<<"not find"<<endl;
//     }
    
    

//     return  0;
// }
class Dog{
    public:
    Dog(string n,int age,double weight):name(n),weight(weight),age(age){}
    operator int() const{//转换操作符
        return age;
    }
    private:
     int age;
     double weight;
     string name;
};

int main()
{
    int b = 0;
    Dog d("a",10,20.0);
    b = d;
    cout<<b<<endl;
    return 0;
}
