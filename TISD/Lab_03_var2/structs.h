#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>
#include <list>
#include <ctime>

#define ERROR -1;
#define CLOCK_PER_SEC 6000;

using namespace std;

typedef int my_type;

struct matrix
{
    my_type *mtrx;
    int rows;
    int columns;
};

struct sparse_matrix
{
    my_type *mtrx;
    int *mtrx_id;
    list <int> columns_id;
    int mtrx_size;
    //int rows; //?
    int columns;
};

int sparse_matrix_malloc(sparse_matrix *m, int columns, int elems_amount);

int sparse_matrix_calloc(sparse_matrix *m, int columns, int elems_amount);

void delete_sparse_matirx(sparse_matrix *m);

int matrix_calloc(matrix *m, int rows, int columns);

void delete_matirx(matrix *m);

void memory_calculating(int rows, int columms, int percent);

#endif // STRUCTS_H
