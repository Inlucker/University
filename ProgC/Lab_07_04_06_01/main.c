#include "functions.h"

void fill_mas(int n, int *mas)
{
    for (int i = 0; i < n; i++)
        mas[i] = 10 - i;
}

void print_mas(int n, int* mas)
{
    for (int i = 0; i < n; i++)
        printf("%d ", mas[i]);
    printf("\n");
}

int get_m (int *mas, int n)
{
    float sr = 0;
    int m = 0;
    for (int i = 0; i < n; i++)
        sr += mas[i];
    sr /= n;
    for (int i = 0; i < n; i++)
        if (mas[i] > sr)
            m++;

    return m;
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

    if (read_file(input_file_name, mas, n) != 0)
        return FILE_READ_ERROR;

    if (filtr_flag)
    {
        int *mas_end = &mas[n];
        int *mas_f = NULL;
        int *mas_f_end = NULL;

        if (key(mas, mas_end, &mas_f, &mas_f_end) != 0)
            return FILTR_ERROR;

        int m = (mas_f_end - mas_f);

        print_mas(m, mas_f);
        mysort(mas_f, m, sizeof(int), (int(*) (const void *, const void *)) comp_int);
        print_mas(m, mas_f);

        if (output(output_file_name, mas_f, m) != 0)
            return FILE_OUTPUT_ERROR;

        if (mas_f)
            free(mas_f);
    }
    else
    {
        print_mas(n, mas);
        mysort(mas, n, sizeof(int), (int(*) (const void *, const void *)) comp_int);
        print_mas(n, mas);

        if (output(output_file_name, mas, n) != 0)
            return FILE_OUTPUT_ERROR;
    }

    if (mas)
        free(mas);

    return 0;

    /*int n = N;
    float *mas = NULL;

    mas = calloc(n, sizeof(float));

    for (int i = 0; i < n/2; i++)
        mas[i] = 69 - i;
    for (int i = n/2; i < n; i++)
        mas[i] = 106 - i;

    for (int i = 0; i < n; i++)
        mas[i] = 10 - i;

    for (int i = 0; i < n; i++)
        printf("%f ", mas[i]);
    printf("\n");

    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mas[i][j] = 83 - i - j;

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%c", mas[i][j]);
        printf("\n");
    }
    printf("\n");

    //puz_sort(mas, n);
    //mysort(mas, n, sizeof(int), (int(*) (const void *, const void *)) comp_int);
    //mysort(mas, n, sizeof(char), (int(*) (const void *, const void *)) comp_char);
    //mysort(mas, n, sizeof(char) * m, (int(*) (const void *, const void *)) comp_string);
    mysort(mas, n, sizeof(float), (int(*) (const void *, const void *)) comp_float);

    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%f", mas[i][j]);
        printf("\n");
    }
    printf("\n");

    for (int i = 0; i < n; i++)
        printf("%f ", mas[i]);
    printf("\n");

    free(mas);

    return 0;*/
}
