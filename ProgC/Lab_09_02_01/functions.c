#include "io_funcs.h"
#include "functions.h"

void quick_sort(struct thing *a, int l, int r)
{
    int i = l, j = r;
    float m = a[(l + r) / 2].p;
    do
    {
        for (; a[i].p < m; i++);
        for (; a[j].p > m; j--);
        if (i <= j)
        {
            struct thing tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
            i++;
            j--;
        }
    }while (i <= j);
    if (l < j)
        quick_sort(a, l, j);
    if (i < r)
        quick_sort(a, i, r);
}
