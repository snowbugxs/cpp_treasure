/*
    哈希算法: 本质上就是取得一个独一无二的识别码, 并且识别码的处理比原先数据容易的多
    核心思想: 将一个数组的值转化为另一数组的下标

*/


#include <stdio.h>
#include <stdlib.h>
#include <ctime>


#define HASH_SIZE 10000
#define SIZE 20

static int Hash_Sort[HASH_SIZE] = {0};

bool hashSort(int * arr, int size)
{
    for(int i = 0; i < size; ++i)
    {
        Hash_Sort[arr[i]]++;
    }
    return true;
}


int main()
{
    int arr_test[SIZE] = {0};
    srand(time(NULL));

    printf("\n生成随机数: \n");
    for(int i = 0; i < SIZE; ++i)
    {
        int temp = rand() % (3 * SIZE);
        arr_test[i] = temp;
        printf("%d  ", temp);
    }
    printf("\n");

    int size = SIZE;
    hashSort(arr_test, size);

    printf("\n排序后: \n");
    for(int i = 0; i < HASH_SIZE && size; ++i )
    {
        while(Hash_Sort[i] != 0)
        {
            printf("%d  ", i);
            Hash_Sort[i]--;
            size--;
        }
    }
    printf("\n排序完成 \n");

    return 0;
}
