#include<iostream>
using namespace std;
class swap{
public:
    swap();
    virtual ~swap();
    void setValue(int value);
    int getValue();
private:
    int a;
};
void swap(int &a,int &b);
