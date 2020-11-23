#ifndef DEFINES_H
#define DEFINES_H

#include <stdio.h>
#include <string.h>

#define N 25
#define M 100
#define L 15
#define CONSOLE_ARGS_ERROR -1
#define FILE_READ_ERROR -2

struct thing
{
    char name[N];
    float m;
    float v;
    float p;
};

#endif // DEFINES_H
