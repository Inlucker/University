#ifndef MTRX_FUNCTIONS_H
#define MTRX_FUNCTIONS_H

#include "defines.h"

double** matrix_malloc(double *mtrx, int rows, int columns);

double** read_mtrx_from_file(char *file_name, double *mtrx, int *rows, int *columns);

void mtrx_addition(double **mtrx_ptrs1, double **mtrx_ptrs2, double **rez_mtrx_ptrs, int rows, int columns);

void print_mtrx(double **mtrx_ptrs, int rows, int columns);

#endif // MTRX_FUNCTIONS_H
