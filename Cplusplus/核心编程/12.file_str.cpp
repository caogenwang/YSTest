#include <iostream>
#include <string>
#include <fstream>
using namespace std;

int main()
{
    fstream ofs;
    ofs.open("test.txt",ios::out);
    ofs<<"姓名：张三"<<endl;
    ofs<<"年龄：18"<<endl;
    ofs<<"性别：男"<<endl;
    ofs.close();


    fstream ifs;

    ifs.open("test.txt",ios::in);
    if (ifs.is_open())
    {

    }
    else
    {
        return 0;
    }
    //1
    // char buf[1024] = {0};
    // while (ifs>>buf)
    // {
    //     cout<<buf<<endl;
    // }
    
    //2
    // char buf[1024] = {0};
    // while (ifs.getline(buf,sizeof(buf)))
    // {
    //     cout<<buf<<endl;
    // }

    //3
    // string buf;
    // while (getline(ifs,buf))
    // {
    //     cout<<buf<<endl;
    // }
    
    //4 
    char c;
    while ((c = ifs.get()) != EOF)
    {
        cout<<c;
    }
    

    ifs.close();

    return 0;
}