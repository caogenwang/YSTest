#include <stdlib.h>
#include <stdio.h>

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


    
    printf("The result array:\n");
    for (int i = 0; i < length; i++)
    {
        printf("%d ",test[i]);
    }
    printf("\n");
    return 0;
}

void mergeSort(int *test,int left,int right){
        if (left<right){
            int middle = (left+right)/2;
            mergeSort(test, 0, middle-1);
            mergeSort(test, middle+1, right);
            merge(test,left,middle,right);
        }
}