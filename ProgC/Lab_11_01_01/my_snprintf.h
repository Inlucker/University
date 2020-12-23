#ifndef MY_SNPRINTF_H
#define MY_SNPRINTF_H
#include <stdio.h>

//int my_snprintf2(char *str, size_t count, const char *fmt, ...);

int convert_unint_to_ho(long value);

char *int_to_str(int n);

int my_snprintf(char *buffer, size_t maxlen, const char *format, ...);

#endif // MY_SNPRINTF_H
