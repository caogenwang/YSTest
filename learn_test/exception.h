#ifndef EXCEPTION_H
#define EXCEPTION_H

#include <iostream>
#include <exception>
using namespace std;
namespace Exception{
    class myexception: public exception{
        virtual const char*what() const throw()
        {
            return "my exception happened";
        }
    }myex;
}

#endif