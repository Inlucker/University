#ifndef IO_FUNCTIONS_H
#define IO_FUNCTIONS_H

#include "defines.h"

int read_args(int argc, char **argv, int *action, char *file_name1, char *file_name2, char *rez_file_name);

double **read_mtrx_from_file(char *file_name, int *r, int *c);

int output_rez(char *rez_file_name, double **mtrx_ptrs, int rows, int columns);

int output_solvation(char *rez_file_name, double **mtrx_ptrs, int rows);

#endif // IO_FUNCTIONS_H
