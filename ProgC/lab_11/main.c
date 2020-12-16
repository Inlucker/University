#include "my_snprintf.h"
#include <string.h>
#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>

#define T 30

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

    char buffer[20] = "lol";

    char *s = "XD LOL KEK";
    char *s2 = "CHEBUREK";
    //int n = (-123) % 65536;
    //n = -123;

    //int rez = -2;
    int rez = my_snprintf(buffer, T, "%s %s", s, s2);
    /*char *buf1 = NULL;
    buf1 = malloc(20);
    sprintf(buf1, "%s", buffer);
    printf("MY_SNPRINTF(buf1):\n%s; %d\n", buf1, rez);
    free(buf1);*/

    printf("MY_SNPRINTF:\n%s; %d\n", buffer, rez);

    snprintf(buffer, 3, "%s", "lol");
    rez = snprintf(buffer, T, "%s %s", s, s2);
    //j = snprintf(buffer, T, "%s %ho", s, n);

    printf("SNPRINTF:\n%s; %d\n", buffer, rez);

    return 0;
}
