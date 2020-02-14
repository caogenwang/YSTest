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

    //1、
    // for (int i = 0; i < length; i++)
    // {
    //     for (int j = 0; j < length; j++)
    //     {
    //         if (test[i] < test[j])
    //         {
    //             int temp = test[i];
    //             test[i] = test[j];
    //             test[j] = temp;
    //          } 
    //     }
    //     printf("exange: ");
    //     for (int m = 0; m < length; m++)
    //     {
    //         printf("%d ",test[m]);
    //     }
    //     printf("\n");
    // }
    //2、
    for (int i = 0; i < 10; i++) {
        for (int j = 0; j < 10 -i - 1; j++) {
            if (test[j + 1] < test[j]) {
                int t = test[j];
                test[j] = test[j+1];
                test[j+1] = t;
            }
        }
        printf("exange: ");
        for (int m = 0; m < length; m++)
        {
            printf("%d ",test[m]);
        }
        printf("\n"); 
    }
    
    printf("The result array:\n");
    for (int i = 0; i < length; i++)
    {
        printf("%d ",test[i]);
    }
    printf("\n");
    return 0;
}