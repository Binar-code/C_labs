#ifndef ARR_LIB_H__
#define ARR_LIB_H__

#include <stdio.h>
#include <stdlib.h>

#define OK 0
#define ARGS_ERR 1
#define OPEN_ERR 2
#define EMPTY_FILE_ERR 3
#define INPUT_ERR 4
#define MEMORY_ALLOCATION_ERR 5
#define EMPTY_ARR_ERR 6

int array_fscan(FILE *file, int **arr_start, int **arr_end);

void array_fprint(FILE *file, int *arr_start, int *arr_end);

int prepare(const int *src_start, const int *src_end, size_t *size);

int key(const int *src_start, const int *src_end, int **dst_start, int **dst_end);

void mysort(void *base, size_t items, size_t size, int (*compar)(const void *, const void *));

int int_compare(const void *a, const void *b);

void swap(void *a, void *b, size_t size);

#endif
