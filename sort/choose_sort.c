#include <stdio.h>
#include <stdlib.h>


int test[10]={2,9,5,6,4,8,7,3,1,0};
int main(int argc,char**argv)
{
    int length = 10;
    printf("The origin array:\n");
    for (int i = 0; i < length; i++)
    {
        printf("%d ",test[i]);
    }
    printf("\n");
    //1、
    // for (int i = 0; i < 10; i++)
    // {
    //     int min = test[i];
    //     int temp = -1;
    //     int position = 0;
    //     for (int j = i+1; j < 10; j++)
    //     {
    //         if (test[j] < min)
    //         {
    //             min = test[j];
    //             position = j;
    //         }
    //     }
    //     if (position == 0)
    //     {
    //         continue;
    //     }
    //     temp = test[i];
    //     test[i] = test[position];
    //     test[position] = temp;
    // }
    //2、on intenet
    for (int i = 0; i < 10; i++)
    {
        int min = i;
        for (int j = i+1; j < 10; j++)
        {
            if (test[j] < test[min])
            {
                min = j;
            }
        }
        int temp = test[i];
        test[i] = test[min];
        test[min] = temp;
    }
    
    printf("The result array:\n");
    for (int i = 0; i < length; i++)
    {
        printf("%d ",test[i]);
    }
    printf("\n");
    return 0;
}