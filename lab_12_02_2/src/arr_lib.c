#include <stdlib.h>
#include "arr_lib.h"

static int fib(int n)
{
    if (n == 1 || n == 2)
        return 1;
    return fib(n - 1) + fib(n - 2);
}

int fib_arr(int *arr, size_t size)
{
    if (arr == NULL)
        return SIZE_ERR;

    for (size_t i = 0; i < size; i++)
            arr[i] = fib(i + 1);
    
    return OK;
}

int filter(int *dst, size_t *new_size, int *src, size_t size)
{
    int is_unique;
    size_t unique_count = 0;

    if (src == NULL || size == 0)
        return SIZE_ERR;

    for (size_t i = 0; i < size; i++)
    {
        is_unique = 1;

        for (size_t j = 0; j < i; j++)
            if (src[i] == src[j])
                is_unique = 0;

        if (is_unique)
        {
            if (dst != NULL)
                dst[unique_count] = src[i];
            unique_count++;
        }
    }

    *new_size = unique_count;
    
    return OK;
}
