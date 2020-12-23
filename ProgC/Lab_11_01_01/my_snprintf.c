#include "defines.h"
#include "my_snprintf.h"
#include <stdarg.h>
#include <string.h>
#include <stdlib.h>
/*
int my_snprintf2(char *str, size_t count, const char *fmt, ...)
{
    va_list param_list;
    va_start(param_list, fmt);

    //int flag = 0;

    size_t rez = 0;
    int simbols = 0;

    for (int i = 0; fmt[i] != '\0'; i++)
    {
        if (fmt[i] == '%')
        {
            i++;
            if (fmt[i] != 's' && fmt[i] != 'h')
                simbols++;
        }
        else
        {
            simbols++;
        }
    }

    char *str_param;

    for (int i = 0; fmt[i] != '\0'; i++)
    {
        if (fmt[i] == '%')
        {
            i++;
            switch (fmt[i])
            {
                case '%':
                    {
                        str[rez] = '%';
                        rez++;
                        break;
                    }
                case 's':
                    {
                        str_param = va_arg(param_list, char*);
                        simbols += strlen(str_param);
                        for (int j = 0; j < strlen(str_param) && rez < count; j++)
                        {
                            str[rez] = str_param[j];
                            rez++;
                        }
                        break;
                    }
                default:
                    {
                        str[rez] = fmt[i];
                        rez++;
                        break;
                    }
            }
        }
        else
        {
            str[rez] = fmt[i];
            rez++;
        }
        if (count - rez <= 0)
        {
            break;
        }
    }

    if (count > rez)
        str[rez] = '\0';
    if (rez < simbols)
    {
        rez = -1;
    }

    va_end(param_list);
    return rez;
}*/

int convert_unint_to_ho(long value)
{
    unsigned long u_value;
    if (value < 0)
    {
        value += TWO_BYTES;
    }
    u_value = value;
    int rez = 0;
    unsigned int mn = 1;
    while (u_value > 0)
    {
        rez += mn * (u_value % 8);
        u_value /= 8;
        mn *= 10;
    }

    return rez;
}

char *int_to_str(int n)
{
    char *rez = malloc(7);

    int tmp = n;
    int i_max = 0;
    while (tmp > 0)
    {
        tmp /= 10;
        i_max++;
    }

    tmp = n;
    int i = 0;
    int mn = 1;
    for (int j = 1; j < i_max; j++)
        mn *= 10;

    if (tmp < 0)
    {
        rez[i] = '-';
        i++;
        i_max++;
        tmp = -tmp;
    }
    while (mn > 0)
    {
        rez[i] = (tmp / mn) + '0';
        tmp %= mn;
        mn /= 10;
        i++;
    }
    rez[i] = '\0';
    return rez;
}

int my_snprintf(char *buffer, size_t maxlen, const char *format, ...)
{
    va_list param_list;
    va_start(param_list, format);

    char *str_param;
    long unint_param;
    size_t rez = 0;
    int flag = DEFAULT;
    int cflags = DEFAULT;

    char ch = *format++;

    while (flag != DONE)
    {
        if (ch == '\0')
            flag = DONE;

        switch (flag)
        {
            case DEFAULT:
                if (ch == '%')
                    flag = MOD;
                else
                {
                    if (rez < maxlen)
                        buffer[rez] = ch;
                    rez++;
                }
                ch = *format++;
                break;
            case MOD:
                switch (ch)
                {
                    case 'h':
                        cflags = SHORT;
                        ch = *format++;
                        break;
                    default:
                        // Skip
                        break;
                }
                flag = CONV;
                break;
            case CONV:
                switch (ch)
                {
                    case '%':
                        if (rez < maxlen)
                            buffer[rez] = ch;
                        rez++;
                        ch = *format++;
                    case 's':
                        str_param = va_arg(param_list, char *);
                        for (int j = 0; j < strlen(str_param); j++)
                        {
                            if (rez < maxlen)
                                buffer[rez] = str_param[j];
                            rez++;
                        }
                        ch = *format++;
                        flag = DEFAULT;
                        //flags = cflags = min = 0;
                        //max = -1;
                        break;
                    case 'o':
                        if (cflags == SHORT)
                            unint_param = va_arg(param_list, unsigned int);
                        else
                            break;
                        int converted_param = convert_unint_to_ho(unint_param);
                        str_param = int_to_str(converted_param);
                        for (int j = 0; j < strlen(str_param); j++)
                        {
                            if (rez < maxlen)
                                buffer[rez] = str_param[j];
                            rez++;
                        }
                        free(str_param);
                        ch = *format++;
                        flag = DEFAULT;
                        break;
                    default:
                        // Unknown, skip
                        break;
                }
                flag = DEFAULT;
                break;
            default:
                // hmm?
                break;
        }
    }

    //buffer[rez] = '\0';
    if (maxlen != 0)
    {
        //buffer[rez] = '\0';
        if (rez < maxlen - 1)
            buffer[rez] = '\0';
        else if (maxlen > 0)
            buffer[maxlen - 1] = '\0';
    }

    va_end(param_list);
    return rez;
}
