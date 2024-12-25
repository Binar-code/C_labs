#include "arr_lib.h"

static int file_size(FILE *file, size_t *count)
{
    int temp_val;
    while (fscanf(file, "%d", &temp_val) == 1)
        (*count)++;
    
    if (!feof(file))
        return INPUT_ERR;

    if (*count == 0)
        return EMPTY_FILE_ERR;

    return OK;
}

int array_fscan(FILE *file, int **arr_start, int **arr_end)
{
    int res;
    int *temp;
    size_t file_pos;
    size_t arr_size = 0;

    file_pos = ftell(file);
    res = file_size(file, &arr_size);
    fseek(file, file_pos, 0);
    if (res != 0 || arr_size == 0)
        return res;

    *arr_start = malloc(arr_size * sizeof(int));
    if (*arr_start == NULL)
        return MEMORY_ALLOCATION_ERR;

    temp = *arr_start;

    while (fscanf(file, "%d", temp) == 1)
        temp++;

    *arr_end = temp;

    return OK;
}

void array_fprint(FILE *file, int *arr_start, int *arr_end)
{
    int *pa;
    for (pa = arr_start; pa < arr_end; pa++)
        fprintf(file, "%d ", *pa);
    fprintf(file, "\n");
}

int prepare(const int *src_start, const int *src_end, size_t *size)
{
    size_t temp_ind = 0;
    int sum = 0;
    const int *pa;

    if (src_start == NULL || src_start == src_end)
        return EMPTY_ARR_ERR;

    for (pa = src_start + 1; pa < src_end; pa++)
        sum += *pa;

    for (pa = src_start; pa < src_end - 1; pa++)
    {
        if (*pa > sum)
            temp_ind++;
        sum -= *(pa + 1);
    }

    if (temp_ind == 0)
        return EMPTY_ARR_ERR;

    *size = temp_ind;

    return OK;
}

int key(const int *src_start, const int *src_end, int **dst_start, int **dst_end)
{
    int sum = 0;
    const int *pa;
    int *pd;

    pd = *dst_start;
    sum = 0;

    for (pa = src_start + 1; pa < src_end; pa++)
        sum += *pa;

    for (pa = src_start; pa < src_end - 1; pa++)
    {
        if (*pa > sum)
        {
            *pd = *pa;
            pd++;
        }
        sum -= *(pa + 1);
    }

    *dst_end = pd;
    return OK;
}

void swap(void *a, void *b, size_t size)
{
    unsigned char *pa = a, *pb = b, temp;
    while (size--)
    {
        temp = *pa;
        *pa++ = *pb;
        *pb++ = temp;
    }
}

int int_compare(const void *a, const void *b)
{
    return (*(int *)a - *(int *)b);
}

void mysort(void *base, size_t items, size_t size, int (*compare)(const void *, const void *))
{
    if (items < 2)
        return;

    unsigned char *arr_start = base;
    unsigned char *arr_end = arr_start + (items - 1) * size;
    unsigned char *last_swap = arr_end, *new_n, *pa;

    while (last_swap > arr_start)
    {
        new_n = arr_start;
        for (pa = arr_start; pa < last_swap; pa += size)
        {
            if (compare(pa, pa + size) > 0)
            {
                swap(pa, pa + size, size);
                new_n = pa;
            }
        }
        last_swap = new_n;
    }
}
