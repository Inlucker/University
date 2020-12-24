#include "defines.h"
#include "read_args.h"
#include "sort_funcs.h"
#include "io_stat_lib.h"
#include "key_stat_lib.h"
#include <stdio.h>
#include <stdlib.h>

void print_mas(int n, int *mas)
{
    for (int i = 0; i < n; i++)
        printf("%d ", mas[i]);
    printf("\n");
}

void print_mas_char(int n, char *mas)
{
    for (int i = 0; i < n; i++)
        printf("%c ", mas[i]);
    printf("\n");
}

void print_mas_double(int n, double *mas)
{
    for (int i = 0; i < n; i++)
        printf("%.2f ", mas[i]);
    printf("\n");
}

int main(int argc, char **argv)
{
    char input_file_name[M] = "";
    char output_file_name[M] = "";
    int filtr_flag = 0;
    int n = 0;
    int *mas = NULL;

    if (read_args(argc, argv, &filtr_flag, input_file_name, output_file_name) != 0)
        return CONSOLE_ARGS_ERROR;

    if (read_file_n(input_file_name, &n) != 0)
        return FILE_READ_ERROR;

    mas = calloc(n, sizeof (int));
    if (!mas)
        return MEMORY_ERROR;

    if (read_file(input_file_name, mas) != 0)
    {
        if (mas)
            free(mas);
        return FILE_READ_ERROR;
    }

    if (filtr_flag)
    {
        int *mas_end = &mas[n];
        int *mas_f = NULL;
        //int *mas_f_end = NULL;

        float sr = 0;
        int n2 = 0;
        int m = 0;

        int *pa = mas;
        for (pa = mas; pa < mas_end; pa++)
        {
            sr += *pa;
            n2++;
        }
        sr /= n2;

        pa = mas;
        for (pa = mas; pa < mas_end; pa++)
        {
            if (*pa > sr)
                m++;
        }

        if (m == 0)
            return FILTR_ERROR;

        mas_f = calloc(m, sizeof (int));
        if (!mas_f)
            return MEMORY_ERROR;

        if (key(mas, mas_end, mas_f, sr, m) != 0)
        {
            free(mas);
            free(mas_f);
            return FILTR_ERROR;
        }

        //int m = (mas_f_end - mas_f);

        print_mas(m, mas_f);

        mysort(mas_f, m, sizeof(int), (int(*)(const void *, const void *)) comp_int);

        print_mas(m, mas_f);

        if (output(output_file_name, mas_f, m) != 0)
        {
            if (mas)
                free(mas);
            if (mas_f)
                free(mas_f);
            return FILE_OUTPUT_ERROR;
        }

        if (mas_f)
            free(mas_f);
    }
    else
    {
        print_mas(n, mas);

        mysort(mas, n, sizeof(int), (int(*)(const void *, const void *)) comp_int);

        print_mas(n, mas);

        if (output(output_file_name, mas, n) != 0)
        {
            if (mas)
                free(mas);
            return FILE_OUTPUT_ERROR;
        }
    }

    if (mas)
        free(mas);
    return 0;
}
