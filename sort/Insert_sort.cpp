#include <stdlib.h>
#include <stdio.h>

int main(int argc,char**argv)
{
    int test[10]={2,9,5,6,4,8,7,3,1,0};

    int length = 10;
    printf("The origin array:\n");
    for (int i = 0; i < length; i++)
    {
        printf("%d ",test[i]);
    }
    printf("\n");

    for (int j = 1; j < length; j++)
    {
        int i = j-1;
        int temp = test[j];
        while (i>-1 && temp < test[i])
        {
            test[i+1] = test[i];
            i--;
        }
        test[i+1] = temp;
    }
    
    printf("The result array:\n");
    for (int i = 0; i < length; i++)
    {
        printf("%d ",test[i]);
    }
    printf("\n");
    return 0;
}