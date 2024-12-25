#include <string.h>
#include "arr_lib.h"

#define DYN_LIB_LOAD_ERR -1
#define DYN_LIB_FUNC_ERR -2

#ifdef DYN_LIB
    #include <dlfcn.h>
#endif

typedef struct {
    int (*array_fscan)(FILE *file, int **arr_start, int **arr_end);
    void (*array_fprint)(FILE *file, int *arr_start, int *arr_end);
    int (*prepare)(const int *src_start, const int *src_end, size_t *size);
    int (*key)(const int *src_start, const int *src_end, int **dst_start, int **dst_end);
    void (*mysort)(void *base, size_t items, size_t size, int (*compar)(const void *, const void *));
    int (*int_compare)(const void *a, const void *b);
    void (*swap)(void *a, void *b, size_t size);
} funcs_t;

int main(int argc, char **argv)
{
    int res;
    int rc = 0;
    int *array = NULL, *array_end = NULL;
    int *filtered_array = NULL, *filtered_array_end = NULL;
    size_t size;
    FILE *file;
    funcs_t funcs;

    #ifdef DYN_LIB
        void *lib = dlopen("./libarr.so", RTLD_NOW);
        if (!lib)
            return DYN_LIB_LOAD_ERR;
        
        funcs.array_fscan = (int (*)(FILE *, int **, int **)) dlsym(lib, "array_fscan");
        if (!funcs.array_fscan)
        {
            dlclose(lib);
            return DYN_LIB_FUNC_ERR;
        }

        funcs.array_fprint = (void (*)(FILE *, int *, int*))  dlsym(lib, "array_fprint");
        if (!funcs.array_fprint)
        {
            dlclose(lib);
            return DYN_LIB_FUNC_ERR;
        }

        funcs.prepare = (int (*)(const int *, const int *, size_t *)) dlsym(lib, "prepare");
        if (!funcs.prepare)
        {
            dlclose(lib);
            return DYN_LIB_FUNC_ERR;
        }

        funcs.key = (int (*)(const int *, const int *, int **, int **)) dlsym(lib, "key");
        if (!funcs.key)
        {
            dlclose(lib);
            return DYN_LIB_FUNC_ERR;
        }

        funcs.mysort = (void (*)(void *, size_t, size_t, int (*)(const void *, const void *))) dlsym(lib, "mysort");
        if (!funcs.mysort)
        {
            dlclose(lib);
            return DYN_LIB_FUNC_ERR;
        }

        funcs.int_compare = (int (*)(const void *, const void *)) dlsym(lib, "int_compare");
        if (!funcs.int_compare)
        {
            dlclose(lib);
            return DYN_LIB_FUNC_ERR;
        }

        funcs.swap = (void (*)(void *, void *)) dlsym(lib, "swap");
        if (!funcs.swap)
        {
            dlclose(lib);
            return DYN_LIB_FUNC_ERR;
        }
    #else
        funcs.array_fscan = array_fscan;
        funcs.array_fprint = array_fprint;
        funcs.prepare = prepare;
        funcs.key = key;
        funcs.mysort = mysort;
        funcs.int_compare = int_compare;
        funcs.swap = swap;
    #endif

    if ((argc < 3) || (argc > 4))
    {
        rc = ARGS_ERR;
        goto close_dynlib;
    }

    if (argc == 4 && strcmp(argv[3], "f") != 0)
    {
        rc = ARGS_ERR;
        goto close_dynlib;
    }

    file = fopen(argv[1], "r");
    if (file == NULL)
    {
        rc = OPEN_ERR;
        goto close_dynlib;
    }

    res = funcs.array_fscan(file, &array, &array_end);
    fclose(file);

    if (res != OK)
    {
        rc = res;
        goto close_dynlib;
    }

    if (argc == 4)
    {
        res = funcs.prepare(array, array_end, &size);
        if (res != OK)
        {
            free(array);
            rc = res;
            goto close_dynlib;
        }

        filtered_array = malloc(size * sizeof(int));

        res = funcs.key(array, array_end, &filtered_array, &filtered_array_end);

        free(array);

        if (res != OK)
        {
            rc = res;
            goto close_dynlib;
        }

        funcs.mysort(filtered_array, filtered_array_end - filtered_array, sizeof(int), funcs.int_compare);

        file = fopen(argv[2], "w");
        if (file == NULL)
        {
            free(filtered_array);
            rc = OPEN_ERR;
            goto close_dynlib;
        }

        funcs.array_fprint(file, filtered_array, filtered_array_end);
        fclose(file);
        free(filtered_array);
    }
    else
    {
        funcs.mysort(array, array_end - array, sizeof(int), funcs.int_compare);

        file = fopen(argv[2], "w");
        if (file == NULL)
        {
            free(array);
            rc = OPEN_ERR;
            goto close_dynlib;
        }

        funcs.array_fprint(file, array, array_end);
        fclose(file);
        free(array);
    }

    close_dynlib:
        #ifdef DYN_LIB
            dlclose(hlib);
        #endif

    return rc;
}
