#include <iostream>
#include <vector>
using namespace std;

class MyString{
    public:
        static size_t DCtor;
        static size_t Ctor;
        static size_t CCtor;
        static size_t MCtor;
        static size_t CAtor;
    private:
        char* _data;
        size_t _len;
        void _init_data(const char *s)
        {
            _data = new char[_len+1];
            memcpy(_data,s,_len);
            _data[_len] = '\0';
        }
    public:
        MyString():_data(nullptr),_len(0){
            ++DCtor;
        }

        MyString(const char*s):_len(std::strlen(s)){
            ++Ctor;
            _init_data(s);
        }

        MyString(const MyString&str):_len(str._len){
            ++CCtor;
            _init_data(str._data);
        }

        MyString(MyString&& str) noexcept
        :_data(str._data),_len(str._len)//NOT COPY！！！！
        {
            ++MCtor;
            str._len = 0;
            str._data = nullptr;//重要
        }

        MyString&operator=(const MyString &str){
            ++CAtor;
            if(this != &str)//自我赋值检查
            {
                if(_data) delete _data;
                _len = str._len;
                _init_data(str._data); //COPY！！！！
            }
            else
            {
                
            }
            return *this;
        }

};