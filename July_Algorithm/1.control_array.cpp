#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <vector>
using namespace std;
/*
control array
A = {4,6,2,5,3,1};
B = {3,4,1,2,1,0};
*/

void CantrolExpansion(const int *a,int *b,int size)// get control array
{
    int i,j;
    for (i = 0; i < size; i++)
    {
        b[i]=0;
        for (j = i + 1; j < size; j++)
        {
            if (a[j] < a[i])
            {
                b[i]++;
            }
        }
    }
}

//从control 数组还原回原始数组
void CantrolExpansionR(const int *a,int *result,int size)
{
    int i;
    vector<int> v(size);
    for (int i = 0; i < size; i++)
    {
        v[i] = i + 1;
    }

    for (int i = 0; i < size; i++)
    {
        result[i] = v[a[i]];
        v.erase(v.begin() + a[i]);
    }
}

void CantrolExpansionR2(int *a,int *result,int size)
{
    memset(result,0,sizeof(int)*size);
    int i,j;
    for (i = 0; i < size; i++)
    {
        for (j = 0; j < size; j++)
        {
            if (result[j] != 0)
                continue;
            if(a[j] == 0)
                break;
            a[j]--;
        }
        result[j] = i + 1;
    }
}

int main(int argc,char**arv)
{
    int c[]={3,4,1,2,1,0};
    int size = 6;
    int b[size];
    CantrolExpansionR2(c,b,size);
    for (int i = 0; i < size; i++)
    {
        cout<<b[i]<<endl;
    }
    return 0;
}