#include "sparse.h"

int get_elems_amount(matrix m)
{
    int rez = 0;
    for (int i = 0; i < m.rows; i++)
        for (int j = 0; j < m.columns; j++)
        {
            if (*((m.mtrx + i*m.columns) + j) != 0)
                rez++;
        }
    return rez;
}

int fill_sparse_matrix(sparse_matrix *rez, matrix m)
{
    rez->mtrx_size = get_elems_amount(m);

    int it = 0;
    list <int> :: iterator iterator = rez->columns_id.begin();
    bool isFirst = true;
    for (int i = 0; i < m.columns; i++)
    {
        for (int j = 0; j < m.rows; j++)
        {
            if (*((m.mtrx + j*m.columns) + i) != 0)
            {
                *(rez->mtrx + it) = *((m.mtrx + j*m.columns) + i);
                *(rez->mtrx_id + it) = j;
                if (isFirst)
                {
                    *iterator = it;
                    isFirst = false;
                    iterator++;
                }
                it++;
            }
        }
        if (isFirst)
            iterator++;
        else
            isFirst = true;
    }
    return 0;
}

int gen_sparse_matrix(sparse_matrix *m, int rows, int columns, int percent)
{
    if (percent <= 0 || percent > 100 || rows <= 0 || columns <= 0)
        return ERROR;
    int elems_amount = (rows * columns * percent) / 100;
    if (elems_amount <= 0 || elems_amount > rows * columns)
        return ERROR;
    sparse_matirx_calloc(m, rows, columns, elems_amount);
    return 0;
}

void print_sparse_matirx(sparse_matrix m)
{
    for (int i = 0; i < m.mtrx_size; i++)
    {
        cout << *(m.mtrx + i) << " ";
    }
    cout << endl;

    for (int i = 0; i < m.mtrx_size; i++)
    {
        cout << *(m.mtrx_id + i) << " ";
    }
    cout << endl;

    for (list <int> :: iterator i = m.columns_id.begin(); i != m.columns_id.end(); ++i)
    {
        cout << (*i) << " ";
    }
    cout << "\n" << endl;
}

int sparse_matrx_sum(sparse_matrix a, sparse_matrix b, sparse_matrix *rez)
{
    if (a.columns != b.columns && a.rows != b.rows)
        return ERROR;
    rez->rows = a.rows;
    rez->columns = a.columns;
    //sparse_matirx_calloc(rez, rez->rows, rez->columns, rez->rows * rez->columns);

    //here
    my_type *tmp1 = new my_type [rez->rows * rez->columns];

    for (int i = 0; i < rez->rows * rez->columns; i++)
    {
        *(tmp1 + i) = 0;
    }

    int i = 0;
    int k = -1;
    int j = a.mtrx_id[i];
    list <int> :: iterator it = a.columns_id.begin();
    while (*it == -1)
    {
        k++;
        it++;
    }

    while (i < a.mtrx_size)
    {
        if (i == *it)
        {
            k++;
            it++;
        }
        *((tmp1 + k * a.rows) + j) = i + 1;
        i++;
        j = a.mtrx_id[i];

    }

    my_type *tmp2 = new my_type [rez->rows * rez->columns];

    for (int i = 0; i < rez->rows * rez->columns; i++)
    {
        *(tmp2 + i) = 0;
    }

    i = 0;
    k = -1;
    j = b.mtrx_id[i];
    it = b.columns_id.begin();
    while (*it == -1 && k < 3)
    {
        k++;
        it++;
    }

    while (i < b.mtrx_size)
    {
        if (i == *it)
        {
            k++;
            it++;
        }
        *((tmp2 + k * b.rows) + j) = i + 1;
        i++;
        j = b.mtrx_id[i];
    }

    for (int i = 0; i < rez->rows * rez->columns; i++)
    {
        cout << *(tmp1 + i) << " ";
    }
    cout << endl;

    for (int i = 0; i < rez->rows * rez->columns; i++)
    {
        cout << *(tmp2 + i) << " ";
    }
    cout << endl;

    //here
    return 0;
}
