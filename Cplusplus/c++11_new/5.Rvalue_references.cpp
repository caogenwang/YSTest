#include <iostream>
#include <vector>
using namespace std;
//右值引用，临时对象，右值没有名称
//左值就是变量，右值不能放在左边
//移动语义和完美转发

class HasPtrMem{
    public:
        HasPtrMem():d(new int(0)){
            cout<<"Construct:"<<++n_cstr<<endl;
        }
        HasPtrMem(const HasPtrMem &h):
            d(new int(*h.d)){
            cout<<"Copy construct:"<<++n_cptr<<endl;
        }
        //移动语义
        HasPtrMem(HasPtrMem && h):d(h.d)//移动构造函数
        {
            h.d = nullptr;
            cout<<"Move construct"<<++n_mptr<<endl;
        }

        HasPtrMem&operator=(const HasPtrMem&d)
        {
            cout<<"Assign construct"<<endl;
            this->d = new int(*d.d);
            return *this;
        }
        ~HasPtrMem(){
            delete d;
            cout<<"Destruct:"<<++n_dstr<<endl;
        }
        int *d;
    private:
        static int n_cstr;
        static int n_cptr;
        static int n_dstr;
        static int n_mptr;
};
int HasPtrMem::n_cstr = 0;
int HasPtrMem::n_cptr = 0;
int HasPtrMem::n_dstr = 0;
int HasPtrMem::n_mptr;
HasPtrMem GetTemp()
{   HasPtrMem h;
    cout<<"GetTemp:"<<h.d<<endl;
    return h;
}

int main(){
    // HasPtrMem b;
    // HasPtrMem a = b;//初始化时候调用copy
    // HasPtrMem c;
    // c = a;//这个时候调用赋值
    // cout<<*a.d<<endl;

    HasPtrMem a = GetTemp();
    cout<<"main:"<<a.d<<endl;
}