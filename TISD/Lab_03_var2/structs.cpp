#include "structs.h"

int sparse_matirx_calloc(sparse_matrix *m, int rows, int columns, int elems_amount)
{
    if (elems_amount <= 0 || rows <= 0 || columns <= 0)
        return ERROR;
    m->mtrx_size = elems_amount;
    m->rows = rows;
    m->columns = columns;

    m->mtrx = new my_type [m->mtrx_size];
    for (int i = 0; i < m->mtrx_size; i++)
    {
        *(m->mtrx + i) = 0;
    }

    m->mtrx_id = new int [m->mtrx_size];
    for (int i = 0; i < m->mtrx_size; i++)
    {
        *(m->mtrx_id + i) = 0;
    }

    for (int i = 0; i < m->columns; i++)
    {
        m->columns_id.push_back(-1);
    }

    return 0;
}

void delete_sparse_matirx(sparse_matrix *m)
{
    delete [] m->mtrx;
    delete [] m->mtrx_id;
    m->columns_id.clear();
}

int matrix_calloc(matrix *m, int rows, int columns)
{
    if (rows < 0 || columns < 0)
        return ERROR;
    m->rows = rows;
    m->columns = columns;

    m->mtrx = new my_type [rows * columns];
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            *((m->mtrx + i*columns) + j) = 0;//i*columns + j + 1;
        }
    }
    return 0;
}

void delete_matirx(matrix *m)
{
    delete [] m->mtrx;
}
