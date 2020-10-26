#ifndef SPARSE_H
#define SPARSE_H

#include "structs.h"

int get_elems_amount(matrix m);

void fill_sparse_matrix(sparse_matrix *rez, matrix m);

int gen_sparse_matrix(sparse_matrix *m, int rows, int columns, int percent);

void print_sparse_matirx(sparse_matrix m);

int sparse_matrx_sum(sparse_matrix a, sparse_matrix b, sparse_matrix *rez);

#endif // SPARSE_H
