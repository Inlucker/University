#include "io_dyn_lib.h"
#include <stdio.h>

#define ARR_EXPORT

ARR_DLL int ARR_DECL read_file_n(char *file_name, int *n)
{
    FILE *f = NULL;
    f = fopen(file_name, "r");

    if (f != NULL)
    {
        int i = 0;
        int input_rez = 0;

        int input = 0;

        while (feof(f) == 0)
        {
            input_rez = fscanf(f, "%d\n", &input);

            if (input_rez != 1)
                return FILE_READ_ERROR;
            i++;
        }
        *n = i;
    }
    else
        return FILE_READ_ERROR;
    fclose(f);

    return 0;
}

ARR_DLL int ARR_DECL read_file(char *file_name, int *mas)
{
    FILE *f = NULL;
    f = fopen(file_name, "r");

    if (f != NULL)
    {
        int i = 0;
        int input_rez = 0;

        int input = 0;

        while (feof(f) == 0)
        {
            input_rez = fscanf(f, "%d\n", &input);

            if (input_rez != 1)
                return FILE_READ_ERROR;

            //printf("%d", mas[i]);
            mas[i] = input;

            i++;
        }
    }
    else
        return FILE_READ_ERROR;
    fclose(f);

    return 0;
}

ARR_DLL int ARR_DECL output(char *file_name, int *mas, int n)
{
    FILE *f = NULL;
    f = fopen(file_name, "w");

    if (f != NULL)
        for (int i = 0; i < n; i++)
            fprintf(f, "%d ", mas[i]);
    else
        return FILE_OUTPUT_ERROR;

    fclose(f);
    return 0;
}
