#include <string.h>
#include "arr_lib.h"

int main(int argc, char **argv)
{
    int res;
    int *array = NULL, *array_end = NULL;
    int *filtered_array = NULL, *filtered_array_end = NULL;
    size_t size;
    FILE *file;

    if ((argc < 3) || (argc > 4))
        return ARGS_ERR;

    if (argc == 4 && strcmp(argv[3], "f") != 0)
        return ARGS_ERR;

    file = fopen(argv[1], "r");
    if (file == NULL)
        return OPEN_ERR;

    res = array_fscan(file, &array, &array_end);
    fclose(file);

    if (res != OK)
        return res;

    if (argc == 4)
    {
        res = prepare(array, array_end, &size);
        if (res != OK)
        {
            free(array);
            return res;
        }

        filtered_array = malloc(size * sizeof(int));

        res = key(array, array_end, &filtered_array, &filtered_array_end);

        free(array);

        if (res != OK)
            return res;

        mysort(filtered_array, filtered_array_end - filtered_array, sizeof(int), int_compare);

        file = fopen(argv[2], "w");
        if (file == NULL)
        {
            free(filtered_array);
            return OPEN_ERR;
        }

        array_fprint(file, filtered_array, filtered_array_end);
        fclose(file);
        free(filtered_array);
    }
    else
    {
        mysort(array, array_end - array, sizeof(int), int_compare);

        file = fopen(argv[2], "w");
        if (file == NULL)
        {
            free(array);
            return OPEN_ERR;
        }

        array_fprint(file, array, array_end);
        fclose(file);
        free(array);
    }

    return OK;
}
