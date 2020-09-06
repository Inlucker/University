#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <string.h>
#include <math.h>

#define N 25
#define M 100
#define CONSOLE_ARGS_ERROR -1
#define FILE_READ_ERROR -2

struct thing
{
	char name[N];
    float m;
    float v;
	float p;
};

void quick_sort(struct thing *a, int l, int r);

int read_args(int argc, char** argv, char* prefix, char* file_name);

int read_file(char *file_name, struct thing list[], int *n);

void output(char *prefix, struct thing list[], int n);

void print(struct thing *list);

#endif // FUNCTIONS_H
