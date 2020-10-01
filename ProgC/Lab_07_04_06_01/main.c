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

int main(int argc, char **argv)
{
    char input_file_name[M] = "";
    char output_file_name[M] = "";
    int filtr = 0;
    int n = 0;
    int *mas = NULL;

    if (read_args(argc, argv, &filtr, input_file_name, output_file_name) != 0)
        return CONSOLE_ARGS_ERROR;

    if (read_file_n(input_file_name, &n) != 0)
        return FILE_READ_ERROR;

    mas = calloc(n, sizeof (int));
    if (!mas)
        return MEMORY_ERROR;

    if (read_file(input_file_name, mas, n) != 0)
        return FILE_READ_ERROR;

    print_mas(n, mas);
    mysort(mas, n, sizeof(int), (int(*) (const void *, const void *)) comp_int);
    print_mas(n, mas);

    if (output(output_file_name, mas, n) != 0)
        return FILE_OUTPUT_ERROR;

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
