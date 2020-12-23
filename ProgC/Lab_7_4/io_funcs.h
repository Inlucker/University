#ifndef IO_FUNCS_H
#define IO_FUNCS_H

#include "defines.h"

int read_file_n(char *file_name, int *n);

int read_file(char *file_name, int *mas);

int read_args(int argc, char **argv, int *filtr, char *input_file_name, char *output_file_name);

int output(char *file_name, int *mas, int n);

#endif // IO_FUNCS_H
