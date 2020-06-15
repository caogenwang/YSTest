#include <iostream>
#include <stdlib.h>
using namespace std;

int main()
{
    void *p = malloc(512);
    free(p);

    void *p3 = ::operator new(512);
    ::operator delete(p3);

}
//三种开辟内存的方式
// 1.new 
//2. array new
//3. placement new