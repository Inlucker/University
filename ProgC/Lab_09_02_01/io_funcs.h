#ifndef IO_FUNCS_H
#define IO_FUNCS_H

#include "defines.h"

int read_args(int argc, char **argv, char *prefix, char *file_name);

struct thing *read_file(char *file_name, int *n);

void print_things(struct thing *mas, int n);

void output(char *prefix, struct thing *list, int n);

void print(struct thing *list);

#endif // IO_FUNCS_H
