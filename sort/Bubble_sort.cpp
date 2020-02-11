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

    for (int i = 0; i < length; i++)
    {
        for (int j = 0; j < length; j++)
        {
            if (test[i] < test[j] )
            {
                int temp = test[i];
                test[i] = test[j];
                test[j] = temp;
             } 
        }
    }
    
    printf("The result array:\n");
    for (int i = 0; i < length; i++)
    {
        printf("%d ",test[i]);
    }
    printf("\n");
    return 0;
}