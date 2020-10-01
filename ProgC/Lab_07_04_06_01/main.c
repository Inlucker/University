#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10
#define L 25
#define CONSOLE_ARGS_ERROR -1
#define FILE_READ_ERROR -2

void swap_int(int *a, int *b)
{
    *a = *a + *b;
    *b = *a - *b;
    *a = *a - *b;
}

int puz_sort(int *mas, int n)
{
    for (int i = 0; i < n; i++)
        if (i % 2 == 0)
        {
            for (int j = n - 1; j >= 0; j--)
                if (mas[j - 1] > mas [j])
                    swap_int(&mas[j - 1], &mas[j]);
        }
        else
        {
            for (int j = 0; j < n; j++)
                if (mas[j + 1] < mas [j])
                    swap_int(&mas[j + 1], &mas[j]);
        }
    return 0;
}

int mysort(void *mas, size_t size_of_mas, size_t size_of_type)
{

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
    int *mas;
    int n = N;
    mas = calloc(n, sizeof(int));
    for (int i = 0; i < n; i++)
        mas[i] = (n - i) * (n - i);

    for (int i = 0; i < n; i++)
        printf("%d ", mas[i]);
    printf("\n");

    puz_sort(mas, n);

    for (int i = 0; i < n; i++)
        printf("%d ", mas[i]);
    printf("\n");

    free(mas);

    return 0;
}
