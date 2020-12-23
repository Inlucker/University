#ifndef MTRX_FUNCTIONS_H
#define MTRX_FUNCTIONS_H

#include "defines.h"

double **matrix_malloc(double **mtrx_rez, int rows, int columns);

double **matrix_malloc2(int rows, int columns);

void free_mtrx(double **mtrx_ptrs);

//double **read_mtrx_from_file(char *file_name, int *rows, int *columns);

void mtrx_addition(double **mtrx_ptrs1, double **mtrx_ptrs2, double **rez_mtrx_ptrs, int rows, int columns);

void mtrx_composition(double **mtrx_ptrs1, double **mtrx_ptrs2, double **mtrx_ptrs3, int rows, int columns, int columns1);

double **solve_mtrx(double **mtrx_ptrs_start, int rows, int columns); //, double *x_mtrx

void print_mtrx(double **mtrx_ptrs, int rows, int columns);

#endif // MTRX_FUNCTIONS_H
