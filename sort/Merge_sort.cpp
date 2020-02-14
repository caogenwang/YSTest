#include <stdlib.h>
#include <stdio.h>

// 合并函数，把两个有序的数组合并起来
// void merge(int *t, int left, int middle, int right)
// {
//     for (int i = middle + 1; i < right; i++)
//     {
//         int temp = t[i];
//         int j = middle;
//         while (j>=left && temp < t[j])
//         {
//             t[j+1] = t[j];
//             j--;
//         }
//         t[j+1]=temp;
//     }
// }

void merge(int* arr, int left, int mid, int right) {
         //先用一个临时数组把他们合并汇总起来
         int* a = new int[right - left + 1];
         int i = left;
         int j = mid + 1;
         int k = 0;
         while (i <= mid && j <= right) {
             if (arr[i] < arr[j]) {
                 a[k++] = arr[i++];
             } else {
                 a[k++] = arr[j++];
             }
         }
         while(i <= mid) a[k++] = arr[i++];
         while(j <= right) a[k++] = arr[j++];
         // 把临时数组复制到原数组
         for (i = 0; i < k; i++) {
             arr[left++] = a[i];
         }
    delete []a;
}

void mergeSort(int *t,int left,int right){
        if (left<right){
            int middle = (left+right)/2;
            mergeSort(t, 0, middle-1);
            mergeSort(t, middle+1, right);
            merge(t,left,middle,right);
        }
}


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

    mergeSort(test,0,9);

    printf("The result array:\n");
    for (int i = 0; i < length; i++)
    {
        printf("%d ",test[i]);
    }
    printf("\n");
    return 0;
}