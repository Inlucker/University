#ifndef IO_FUNCS_H
#define IO_FUNCS_H

#include "defines.h"

#define FILE_READ_ERROR -2
#define FILE_OUTPUT_ERROR -4

int read_file_n(char *file_name, int *n);

int read_file(char *file_name, int *mas);

int output(char *file_name, int *mas, int n);

#endif // IO_FUNCS_H
