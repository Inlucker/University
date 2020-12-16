#include "my_snprintf.h"
#include <stdio.h>
#include <stdarg.h>

#define T 5

double avg(int n, ...)
{
    va_list vl;
    double sum = 0, num;

    if (!n)
        return 0.0;

    va_start(vl, n);

    for (int i = 0; i < n; i++)
    {
        num = va_arg(vl, double);

        printf("%f\n", num);

        sum += num;
    }
    va_end(vl);

    return sum /n;
}

int main()
{
    //printf("Hello World!\n");
    //double a = avg(4, 1.0, 2.0, 3.0, 4.0);

    //printf("a = %5.2f\n", a);

    char buffer[4] = "lold";

    char *s = "XDXDXD";
    //int n = (-123) % 65536;
    //n = -123;

    int j = my_snprintf(buffer, T, "%s", s);

    printf("MY_SNPRINTF:\nstring:\n%s\ncharacter count = %d\n\n",buffer, j);

    j = snprintf(buffer, T, "%s", s);

    printf("SNPRINTF:\nstring:\n%s\ncharacter count = %d\n\n",buffer, j);

    return 0;
}
