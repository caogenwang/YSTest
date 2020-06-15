#include <iostream>
#include <vector>
using namespace std;
int a[] = {1,2,3,4,5};
int size = 5;
int sum = 10;
void print(bool *x);
void EnumNumber(bool *x,int i,int has,int size)
{
    if(i > size)
        return;
    if(has + a[i] == sum)
    {
        x[i]=true;
        print(x);
        x[i]=false;
    }

    x[i]=true;
    EnumNumber(x,i+1,has+a[i],size);
    x[i] = false;
    EnumNumber(x,i+1,has,size);
}

void FindNumber(bool*x,int i,int has,int residue,int size)
{
    if(i >= size)
        return;
    if(has+a[i]==sum)
    {
        x[i]=true;
        print(x);
        x[i]=false;
    }
    else if((has + residue >= sum) && (has + a[i] <= sum))
    {
        x[i] = true;
        FindNumber(x,i+1,has+a[i],residue-a[i],size);
    }
    else
    {
        x[i] = false;
        FindNumber(x,i+1,has,residue-a[i],size);
    }
}

int main()
{
    return 0;
}