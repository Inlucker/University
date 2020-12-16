#include "my_snprintf.h"
#include <stdarg.h>
#include <string.h>

int my_snprintf(char *str, size_t count, const char *fmt,...)
{
    va_list param_list;
    va_start(param_list, fmt);

    //int flag = 0;

    int rez = 0;
    int simbols = 0;

    for (int i = 0; fmt[i] != '\0'; i++)
    {
        if (fmt[i]== '%')
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
        if (fmt[i]== '%')
        {
            i++;
            switch (fmt[i])
            {
            case '%':
                str[rez] = '%';
                rez++;
                break;
            case 's':
                str_param = va_arg(param_list, char*);
                simbols +=  strlen(str_param);
                for (int j = 0; j < strlen(str_param) && rez < count; j++)
                {
                    str[rez] = str_param[j];
                    rez++;
                }
                break;
            default:
                str[rez] = fmt[i];
                rez++;
                break;
            }
        }
        else
        {
            str[rez] = fmt[i];
            rez++;
            //simbols++;
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
}


/*int my_snprintf(char *str, size_t count, const char *fmt, ...)
{
    va_list param_list;
    va_start(param_list, fmt);

    int rez = 0;

    char *param;
    int len;

    for (int i = 0; fmt[i] != 0; i++)
    {
        if (count - rez <= 0)
            break;
        else if (fmt[i] == '%')
        {
            i++;
            switch (fmt[i])
            {
            case '%':
                str[rez] = '%';
                rez++;
                break;
            case 's':
                param = va_arg(param_list, char *);
                len = strnlen(param, count - rez);
                strncpy(str + rez, param, len);
                rez += len;
                break;
            default:
                printf("Invalid format.\n");
                va_end(param_list);
                return -1;
            }
        }
        else
            str[rez++] = fmt[i];
    }

    //if (rez == count) rez--;
    str[rez] = 0;

    va_end(param_list);
    return rez;
}*/
