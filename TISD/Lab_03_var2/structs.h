#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>
#include <list>
#include <ctime>

#define ERROR -1;

using namespace std;

typedef double my_type;

struct matrix
{
    my_type *mtrx;
    int rows;
    int columns;
};

/*struct list
{
    int value;
    int *next_ptr = NULL;
};*/

struct sparse_matrix
{
    my_type *mtrx;
    int *mtrx_id;
    list <int> columns_id;
    int mtrx_size;
    int rows; //?
    int columns;
};

int sparse_matirx_calloc(sparse_matrix *m, int rows, int columns, int elems_amount);

void delete_sparse_matirx(sparse_matrix *m);

int matrix_calloc(matrix *m, int rows, int columns);

void delete_matirx(matrix *m);

#endif // STRUCTS_H
