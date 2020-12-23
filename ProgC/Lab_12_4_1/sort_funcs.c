#include "sort_funcs.h"
#include "defines.h"

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

int comp_double(const double *i, const double *j)
{
    int rez = 0;
    if (*i - *j > EPS)
        rez = 1;
    else if (*j - *i > EPS)
        rez = -1;
    return rez;
}

int comp_char(const char *i, const char *j)
{
    int rez = 0;
    char tmp1 = *i;
    char tmp2 = *j;
    if (tmp1 < 'a')
        tmp1 += 'a' - 'A';

    if (tmp2 < 'a')
        tmp2 += 'a' - 'A';

    if (tmp1 < tmp2)
        rez = -1;
    else if (tmp1 > tmp2)
        rez = 1;
    else
        rez = 0;
    return rez;
}

int mysort(void *mas, size_t size_of_mas, size_t size_of_type, int(*comparator)(const void *, const void *))
{
    for (int i = 0; i < size_of_mas; i++)
        if (i % 2 == 0)
        {
            for (int j = size_of_mas - 1; j > 0; j--)
            {
                char *pa = (char*)mas + j * size_of_type;
                if (comparator(pa - size_of_type, pa) > 0)
                    swap(pa - size_of_type, pa, size_of_type);
            }
        }
        else
        {
            for (int j = 0; j < size_of_mas - 1; j++)
            {
                char *pa = (char*)mas + j * size_of_type;
                if (comparator(pa + size_of_type, pa) < 0)
                    swap(pa + size_of_type, pa, size_of_type);
            }
        }
    return 0;
}
