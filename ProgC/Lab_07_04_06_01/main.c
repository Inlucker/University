#include "functions.h"

int main()
{
    int n = N;
    int m = M;
    float *mas = NULL;

    /*mas = allocate_matrix_2(n, m);
    if (mas == NULL)
        return -1;*/

    mas = calloc(n, sizeof(float));

    /*for (int i = 0; i < n/2; i++)
        mas[i] = 69 - i;
    for (int i = n/2; i < n; i++)
        mas[i] = 106 - i;*/

    for (int i = 0; i < n; i++)
        mas[i] = 10 - i;

    for (int i = 0; i < n; i++)
        printf("%f ", mas[i]);
    printf("\n");

    /*for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            mas[i][j] = 83 - i - j;*/

    /*for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%c", mas[i][j]);
        printf("\n");
    }
    printf("\n");*/

    //puz_sort(mas, n);
    //mysort(mas, n, sizeof(int), (int(*) (const void *, const void *)) comp_int);
    //mysort(mas, n, sizeof(char), (int(*) (const void *, const void *)) comp_char);
    //mysort(mas, n, sizeof(char) * m, (int(*) (const void *, const void *)) comp_string);
    mysort(mas, n, sizeof(float), (int(*) (const void *, const void *)) comp_float);

    /*for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < m; j++)
            printf("%f", mas[i][j]);
        printf("\n");
    }
    printf("\n");*/

    for (int i = 0; i < n; i++)
        printf("%f ", mas[i]);
    printf("\n");

    free(mas);

    return 0;
}
