#include <stdio.h>
#include <stdlib.h>

int main(int argc,char**argv)
{
    int a[3][4];
    for (int i = 0; i < 3; i ++) {
        for (int j = 0; j < 4; j ++) {
            a[i][j] = i*4 + j;
        }
    }
    
    int (*p)[4] = a;
    for (int i = 0; i < 3; i ++) {
        for (int j = 0; j < 4; j ++) {
            printf("%d\n",*( *(p + i) + j) );
        }
    }
    return 0;
}
