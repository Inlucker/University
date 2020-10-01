/*!
  \file
  \brief Исходный файл содержащий в себе реализации всех используемых функций
  */
#include "functions.h"

/*void swap_int(int *a, int *b)
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}*/

/*int puz_sort(int *mas, int n)
{
    for (int i = 0; i < n; i++)
        if (i % 2 == 0)
        {
            for (int j = n - 1; j > 0; j--)
                if (mas[j - 1] > mas [j])
                    swap_int(&mas[j - 1], &mas[j]);
        }
        else
        {
            for (int j = 0; j < n - 1; j++)
                if (mas[j + 1] < mas [j])
                    swap_int(&mas[j + 1], &mas[j]);
        }
    return 0;
}*/

/*double ** allocate_matrix_2(int n, int m)
{
    double**data = malloc(n * sizeof(double*) + n * m * sizeof(double));

    if (!data)
        return NULL;

    for(int i = 0; i < n; i++)
        data[i] = (double*)((char*)data + n * sizeof(double*) + i * m * sizeof(double));

    return data;
}*/

void swap(void *a, void *b, size_t size_of_type)
{
    char *tmp_a = a;
    char *tmp_b = b;
    size_t tmp_size = size_of_type;
    do
    {
        char tmp = *tmp_a;
        *tmp_a++ = *tmp_b;
        *tmp_b++ = tmp;
    } while (--tmp_size > 0);
}

int comp_int(const int *i, const int *j)
{
    return *i - *j;
}

int comp_float(const float *i, const float *j)
{
    float rez = *i - *j;
    if (rez > 0)
        return 1;
    else if (rez < 0)
        return -1;
    else
        return 0;
}

int comp_char(const char *i, const char *j)
{
    char tmp1 = *i;
    char tmp2 = *j;

    if (tmp1 < 97)
        tmp1 += 32;

    if (tmp2 < 97)
        tmp2 += 32;

    if(tmp1 < tmp2)
        return -1;
    else if (tmp1 > tmp2)
        return 1;
    else
        return 0;
}

int comp_string(const char *i, const char *j)
{
    while (comp_char(i, j) == 0 && *i != '\0' && *j != '\0')
    {
        *i++;
        *j++;
    }
    return comp_char(i, j);
}

int mysort(void *mas, size_t size_of_mas, size_t size_of_type, int ( * comparator ) ( const void *, const void * ))
{
    for (int i = 0; i < size_of_mas; i++)
        if (i % 2 == 0)
        {
            for (int j = size_of_mas - 1; j > 0; j--)
                if (comparator(&mas[j * size_of_type - size_of_type], &mas[j * size_of_type]) > 0)
                    swap(&mas[j * size_of_type - size_of_type], &mas[j * size_of_type], size_of_type);
                    //SWAP(&mas[j * size_of_type - size_of_type], &mas[j * size_of_type], size_of_type);
        }
        else
        {
            for (int j = 0; j < size_of_mas - 1; j++)
                if (comparator(&mas[j * size_of_type + size_of_type], &mas[j * size_of_type]) < 0)
                    swap(&mas[j * size_of_type + size_of_type], &mas[j * size_of_type], size_of_type);
                    //SWAP(&mas[j * size_of_type + size_of_type], &mas[j * size_of_type], size_of_type);
        }
    return 0;
}

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst)
{
    int *mas_f = NULL;
    float sr = 0;
    int n = 0;
    int m = 0;

    int *pa = pb_src;
    for (pa = pb_src; pa < pe_src; pa++)
    {
        sr += *pa;
        n++;
    }
    sr /= n;

    for (pa = pb_src; pa < pe_src; pa++)
    {
        if (*pa > sr)
            m++;
    }

    mas_f = calloc(m, sizeof (int));
    if (!mas_f)
        return MEMORY_ERROR;

    int j = 0;
    for (pa = pb_src; pa < pe_src; pa++)
    {
        if (*pa > sr)
        {
            mas_f[j] = *pa;
            j++;
        }
    }

    *pb_dst = mas_f;
    *pe_dst = &mas_f[m];

    return 0;
}

int read_file_n(char *file_name, int *n)
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

            if (input_rez == -1)
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

int read_file(char *file_name, int *mas, int n)
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

            if (input_rez == -1)
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

int read_args(int argc, char **argv, int *filtr, char *input_file_name, char *output_file_name)
{
    switch (argc)
    {
        case 3:
            if (strlen(argv[1]) > M || strlen(argv[2]) > M)
                return CONSOLE_ARGS_ERROR;
            strcpy(input_file_name, argv[1]);
            strcpy(output_file_name, argv[2]);
            *filtr = 0;
            break;
        case 4:
            if (strlen(argv[1]) > M || strlen(argv[2]) > M)
                return CONSOLE_ARGS_ERROR;
            strcpy(input_file_name, argv[1]);
            strcpy(output_file_name, argv[2]);
            if (strcmp(argv[3], "f") == 0)
                *filtr = 1;
            else
                *filtr = 0;
            break;
        default:
            return CONSOLE_ARGS_ERROR;
            break;
    }
    return 0;
}

int output(char *file_name, int *mas, int n)
{
    FILE *f = NULL;
    f = fopen(file_name, "w");

    if (f != NULL)
        for (int i = 0; i < n; i++)
            fprintf(f, "%d\n", mas[i]);
    else
        return FILE_OUTPUT_ERROR;

    fclose(f);
    return 0;
}
