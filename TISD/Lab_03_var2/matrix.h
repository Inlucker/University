#ifndef MATRIX_H
#define MATRIX_H

#include "structs.h"

int gen_matrix(matrix *m, int rows, int columns, int percent);

void print_matrix(matrix m);

int matrx_sum(matrix a, matrix b, matrix *rez);

#endif // MATRIX_H
