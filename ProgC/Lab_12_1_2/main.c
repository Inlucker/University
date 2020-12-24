#include <stdio.h>
#include <stdlib.h>
#include "mylib.h"

void print_mas(int *mas, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", mas[i]);
    }
    printf("\n");
}

int main()
{
    int n = 4;
    int *mas = malloc(n * sizeof (int));
    for (int i = 0; i < n; i++)
    {
        mas[i] = i + 1;
    }
    print_mas(mas, n);
    int k = 9122;
    sdvig(mas, n, k);
    print_mas(mas, n);

    printf("%d %d", isSquare(27), isSquare(121));

    return 0;
}
