#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10
#define L 25
#define CONSOLE_ARGS_ERROR -1
#define FILE_READ_ERROR -2

/*
#define SWAP(a, b, size)                                                      \
  do                                                                              \
    {                                                                              \
      size_t __size = (size);                                                      \
      char *__a = (a), *__b = (b);                                              \
      do                                                                      \
        {                                                                      \
          char __tmp = *__a;                                                      \
          *__a++ = *__b;                                                      \
          *__b++ = __tmp;                                                      \
        } while (--__size > 0);                                                      \
    } while (0)
*/

/*void swap_int(int *a, int *b)
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
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

// int compare
int comp_int (const int *i, const int *j)
{
    return *i - *j;
}

int comp_char (const char *i, const char *j)
{
    if(*i < *j)
        return -1;
    else if (*i > *j)
        return 1;
    else
        return 0;
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



int read_file(char *file_name, void *mas, int *n)
{
    FILE *f = NULL;
    f = fopen(file_name, "r");

    if (f != NULL)
    {
        int i = 0;
        int input_rez = 0;

        char input[L];
        input_rez = fscanf(f, "%s\n", input);

        if (input_rez == -1)
            return FILE_READ_ERROR;

        while (feof(f) == 0)
        {
            input_rez = fscanf(f, "%s\n", input);

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


int main()
{
    char *mas;
    int n = N;
    mas = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
        mas[i] = 74 - i;

    for (int i = 0; i < n; i++)
        printf("%c ", mas[i]);
    printf("\n");

    //puz_sort(mas, n);
    //mysort(mas, n, sizeof(int), (int(*) (const void *, const void *)) comp_int);
    mysort(mas, n, sizeof(char), (int(*) (const void *, const void *)) comp_char);

    for (int i = 0; i < n; i++)
        printf("%c ", mas[i]);
    printf("\n");

    free(mas);

    return 0;
}
