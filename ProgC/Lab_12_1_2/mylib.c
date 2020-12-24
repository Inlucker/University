#define ARR_EXPORT

#include "mylib.h"

int isSquare(long long int x)
{
    for (int i = 1; x > 0; x -= i, i+=2);
    return !x;
}

ARR_DLL int ARR_DECL get_new_mas(int *src, int src_len, int *dst, int *dst_len)
{
    int m;

    m = 0;
    for (int i = 0; i < src_len; i++)
        if (isSquare(src[i]))
            m++;

    if (m > *dst_len)
    {
        *dst_len = m;

        return 1;
    }

    m = 0;
    for (int i = 0; i < src_len; i++)
        if (isSquare(src[i]))
        {
            dst[m] = src[i];
            m++;
        }

    *dst_len = m;

    return 0;
}

ARR_DLL void ARR_DECL sdvig(int* mas, int n, int k)
{
    if (mas)
    {
        k %= n;
        for (int i = 0; i < k; i++)
        {
            int first = mas[0];
            for (int i = 0; i < n - 1; i++)
            {
                mas[i] = mas[i + 1];
            }
            mas[n - 1] = first;
        }
    }
}

ARR_DLL int ARR_DECL add(int a, int b)
{
    return a + b;
}

ARR_DLL int ARR_DECL divide(int a, int b, int *remainder)
{
    int quot = a / b;

    *remainder = a % b;

    return quot;
}


ARR_DLL void ARR_DECL fill_array(double *arr, int n)
{
    for (int i = 0; i < n; i++)
        arr[i] = i;
}


ARR_DLL double ARR_DECL avg(double *arr, int n)
{
    double sum = 0.0;

    for (int i = 0; i < n; i++)
        sum += arr[i];

    return sum / n;
}


ARR_DLL int ARR_DECL filter(double *src, int src_len, double *dst, int *dst_len)
{
    int n;

    n = 0;
    for (int i = 0; i < src_len; i++)
        if (src[i] < 0)
            n++;

    if (n > *dst_len)
    {
        *dst_len = n;

        return 1;
    }

    n = 0;
    for (int i = 0; i < src_len; i++)
        if (src[i] < 0)
        {
            dst[n] = src[i];
            n++;
        }

    *dst_len = n;

    return 0;
}
