#include "header.h"

#define SIZE 10
int main(void)
{
    int *arr = _malloc(SIZE);
    int *arr2 = _malloc(SIZE);
    int *arr3 = tmalloc(SIZE);

    if (!arr)
    {
        printf("malloc faild\n");
        exit(1);
    }
    _free();
    _free_env();

}