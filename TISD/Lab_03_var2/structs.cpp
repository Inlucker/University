#include "structs.h"

int sparse_matrix_malloc(sparse_matrix *m, int columns, int elems_amount)
{
    if (elems_amount <= 0 || columns <= 0)
        return ERROR;
    m->mtrx_size = elems_amount;
    //m->rows = rows;
    m->columns = columns;

    m->mtrx = new my_type [m->mtrx_size];

    m->mtrx_id = new int [m->mtrx_size];

    for (int i = 0; i < m->columns; i++)
    {
        m->columns_id.push_back(-1);
    }

    return 0;
}

int sparse_matrix_calloc(sparse_matrix *m, int columns, int elems_amount)
{
    if (elems_amount <= 0 || columns <= 0)
        return ERROR;
    m->mtrx_size = elems_amount;
    //m->rows = rows;
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

void memory_calculating(int rows, int columns, int percent)
{
    long long int r = rows, c = columns, p = percent;
    long long int elems_amount = (r * c * p) / 100;
    if (elems_amount == 0)
        elems_amount = 1;
    //int matrix_memory = sizeof (int) * (rows * columns) + sizeof (matrix);
    //int sparse_matrix_memory = (sizeof(int) + sizeof(my_type)) * elems_amount + sizeof (sparse_matrix);
    //cout << sizeof (list <int>) << " bytes." << endl;
    cout << "Default matrix: " << sizeof (my_type) * (rows * columns) + sizeof (matrix) << " bytes. Sparse matrix: " << (sizeof(int) + sizeof(my_type)) * elems_amount
          + ((sizeof(int) + 2 * sizeof(int*)) * columns) + sizeof (sparse_matrix) << " bytes." << endl;
}
