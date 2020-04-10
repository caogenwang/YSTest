#include <iostream>
#include <string>
using namespace std;

class Sales_item{
    public:
        Sales_item():isbn(nullptr),units_sold(0),revernue(0){
            cout<<"construct1"<<endl;
        };
        Sales_item(const string &book):isbn(book),units_sold(0),revernue(0){
            cout<<"construct2"<<endl;
        };

        //复制构造函数
        Sales_item(const Sales_item &orig):isbn(orig.isbn),units_sold(orig.units_sold),revernue(orig.revernue)
        {
            cout<<"copy construct"<<endl;
        }

        //赋值操作符
        Sales_item & operator =(const Sales_item &orig)
        {
            cout<<"== construct"<<endl;
            isbn = orig.isbn;
            units_sold = orig.units_sold;
            revernue = orig.revernue;
            return *this;
        }
    private:
        string isbn;
        unsigned int units_sold;
        double revernue;
};

Sales_item foo(Sales_item item)
{
    Sales_item temp;
    temp = item;
    return temp;
}
class NoName{
    public:
    NoName():pstring(new string),i(0),d(0.0){}
    NoName(const NoName &other)
    :pstring(new string(*(other.pstring))),i(other.i),d(other.d){
        cout<<"copy contruct"<<endl;
    }
    NoName & operator= (const NoName &rhs)
    {
        pstring = new string();
        *pstring = *(rhs.pstring);
        i = rhs.i;
        d = rhs.d;
    }
    private:
        std::string *pstring;
        int i;
        double d;
};
int main()
{
    Sales_item s;
    return 0;
}