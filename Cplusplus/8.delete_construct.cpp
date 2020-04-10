#include <iostream>
#include <string>
using namespace std;

class NoName{
    public:
    NoName():pstring(new string),i(0),d(0.0){
        //打开文件
        //连接数据库
        //动态分配内存
        cout<<"contruct"<<endl;
    }
    ~NoName();
    NoName(const NoName &other)
    :pstring(new string(*(other.pstring))),i(other.i),d(other.d){
        cout<<"copy contruct"<<endl;
    }
    NoName & operator= (const NoName &rhs)
    {
        cout<<"== contruct"<<endl;
        pstring = new string();
        *pstring = *(rhs.pstring);
        i = rhs.i;
        d = rhs.d;
        return *this;
    }
    private:
        std::string *pstring;
        int i;
        double d;
};

NoName::~NoName()
{
    //关闭文件
    //关闭数据库
    //动态释放内存
    cout<<"delete fun"<<endl;
    delete pstring;
}
//三原则,必须写赋值，复制构造函数

int main()
{

    NoName a;
    NoName *p = new NoName();
    delete p;
    return 0;
}