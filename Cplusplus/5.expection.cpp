#include <iostream>
#include <algorithm>
#include <vector>
#include <set>
#include <string>
using namespace std;
// 1.传统方法
// int my_cp(const char *src_file,const char *src_des)
// {
//     FILE *infile ,*outfile;
//     infile = fopen(src_file,"rb");
//     if(infile == nullptr)
//     {
//         return 1;
//     }
    
//     outfile = fopen(src_des,"wb");
//     if(outfile == nullptr)
//     {
//         return 2;
//     }

//     char res[256];
//     size_t bin,bout;
//     while((bin = fread(res,1,256,infile))>0)
//     {
//         bout = fwrite(res,1,bin,outfile);
//         if(bin != bout)
//         {
//             return 3;
//         }
//     }
//     return 0;
// }

void my_cp2(const char *src_file,const char *src_des)
{
    FILE *infile ,*outfile;
    infile = fopen(src_file,"rb");
    if(infile == nullptr)
    {
        throw "1";
    }
    
    outfile = fopen(src_des,"wb");
    if(outfile == nullptr)
    {
        throw "2";
    }

    char res[256];
    size_t bin,bout;
    while((bin = fread(res,1,256,infile))>0)
    {
        bout = fwrite(res,1,bin,outfile);
        if(bin != bout)
        {
            // throw 3;
            throw "3";
        }
    }
}

class BadSrcFile{};
class BadDesFile{};
class BadWriFile{};
void my_cp4(const char *src_file,const char *src_des)
{
    FILE *infile ,*outfile;
    infile = fopen(src_file,"rb");
    if(infile == nullptr)
    {
        // throw "1";
        throw BadSrcFile();
    }
    
    outfile = fopen(src_des,"wb");
    if(outfile == nullptr)
    {
        // throw "2";
        throw BadDesFile();
    }

    char res[256];
    size_t bin,bout;
    while((bin = fread(res,1,256,infile))>0)
    {
        bout = fwrite(res,1,bin,outfile);
        if(bin != bout)
        {
            // throw 3;
            // throw "3";
            throw BadWriFile();
        }
    }
}

// int main()
// {
//     // int result = 0;
//     // result = my_cp("1.txt","1_copy.txt");
//     // switch (result)
//     // {
//     // case 1:
//     //     cout<<"error src"<<endl;
//     //     break;
//     // case 2:
//     //     cout<<"error des"<<endl;
//     //     break;
//     // case 3:
//     //     cout<<"error write"<<endl;
//     //     break;
//     // default:
//     //     break;
//     // }
//     try
//     {
//         my_cp4("1.txt1","1_copy.txt");
//     }
//     catch(const char* e)
//     {
//         // std::cerr << e.what() << '\n';
//         printf("char:%s\n",e);
//     }catch(int a)
//     {   
//         printf("int:%d\n",a);
//     }catch(BadSrcFile e)
//     {
//         printf("BadSrcFile\n");
//     }
//     catch(BadDesFile e)
//     {
//         printf("BadDesFile\n");
//     }
//     catch(BadWriFile e)
//     {
//         printf("BadWriFile\n");
//     }
//     // catch(...)所有的异常,抓住漏网之鱼
//     // {

//     // }
    
//     printf("OK!\n");
//     return 0;
// }

// 异常层次结构,设计异常类，创建自己的异常类
// 异常派生
// 议程中的数据成员
// 按引用传递异常
const int DefaultSize = 10;

class xBoundry{};
class Array{
    public:
        Array(int itsSize = DefaultSize);
        ~Array(){delete[]pType;};
        //访问器
        int GetSize() const {return itsSize;}
        //下标运算符
        int &operator [](int offset);
        const int &operator [](int offset) const;
    private:
        int *pType;
        int itsSize;
};

Array::Array(int size):itsSize(size)
{
    pType = new int[size];
    for (int i = 0; i < size; i++)
    {
        pType[i] = 0;
    }
}

int &Array::operator[](int offset)
{
    int size = this->GetSize();
    if (offset >= 0 && offset < size)
    {
        return pType[offset];
    }
    else
    {
        throw xBoundry();
    }
}

const int &Array::operator[](int offset) const
{
    int size = this->GetSize();
    if (offset >= 0 && offset < size)
    {
        return pType[offset];
    }
    else
    {
        throw xBoundry();
    }
}

int main()
{
    Array a(10);
    try
    {
         a[22] = 0;
    }
    catch(...)
    {
        printf("异常\n");
    }
    cout<<"OK!"<<endl;
    return 0;
}
