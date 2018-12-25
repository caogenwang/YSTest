#ifndef CLASS_TEST_H
#define CLASS_TEST_H
#include <iostream>
using namespace std;

class Base
{
    public:
        Base();
        Base(const Base&);
        virtual~Base();
        int get_value();
        int get_static_value();
        Base &operator=(const Base &);
    private:
        int a;
        static int b;
};

#endif