#include "matrix.h"

int gen_matrix(matrix *m, int rows, int columns, int percent)
{
    if (percent <= 0 || percent > 100 || rows <= 0 || columns <= 0)
        return ERROR;
    long long int r = rows, c = columns, p = percent;
    long long int elems_amount = (r * c * p) / 100;
    //printf("%d\n", elems_amount);
    if (elems_amount == 0)
        elems_amount = 1;
    //cout << elems_amount << endl;

    int cur_el_number = 0;

    m->rows = rows;
    m->columns = columns;

    while (cur_el_number < elems_amount)
    {
        int i = rand() % rows;
        int j = rand() % columns;
        while (*((m->mtrx + i*columns) + j) != 0)
        {
            i = rand() % rows;
            j = rand() % columns;
        }
        *((m->mtrx + i*columns) + j) = rand() % 100 + 1;
        cur_el_number++;
    }
    return 0;
}

int gen_matrix2(matrix *m, int rows, int columns, int percent)
{
    if (percent <= 0 || percent > 100 || rows <= 0 || columns <= 0)
        return ERROR;
    long long int r = rows, c = columns, p = percent;
    long long int elems_amount = (r * c * p) / 100;
    if (elems_amount == 0)
        elems_amount = 1;
    //cout << elems_amount << endl;

    int cur_el_number = 0;

    m->rows = rows;
    m->columns = columns;

    while (cur_el_number < elems_amount)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (rand() % 2 == 1 && *((m->mtrx + i*columns) + j) == 0)
                {
                    *((m->mtrx + i*columns) + j) = rand() % 100 + 1;
                    cur_el_number++;
                }
                if (cur_el_number >= elems_amount)
                    break;
            }
            if (cur_el_number >= elems_amount)
                break;
        }
    }
    return 0;
}

void fill_matrix(matrix *rez, sparse_matrix m)
{
    int cur_m_id = 0;
    list <int> :: iterator it = m.columns_id.begin();
    for (int i = 0; i < rez->columns; i++)
    {
        for (int j = 0; j < rez->rows; j++)
        {
            if (j == *(m.mtrx_id + cur_m_id) && *it != -1)
            {
                *((rez->mtrx + j * rez->columns) + i) = *(m.mtrx + cur_m_id);
                cur_m_id++;
            }
            else
                *((rez->mtrx + j * rez->columns) + i) = 0;
        }
        it++;
    }
}

void print_matrix(matrix m)
{
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.columns; j++)
        {
            printf("%3d ", *((m.mtrx + i * m.columns) + j));
            //cout << *((m.mtrx + i * m.columns) + j) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

int matrx_sum(matrix a, matrix b, matrix *rez)
{
    if (a.columns != b.columns && b.columns != rez->columns && a.rows != b.rows && b.rows != rez->rows)
        return ERROR;
    for (int i = 0; i < rez->rows; i++)
    {
        for (int j = 0; j < rez->columns; j++)
        {
            *((rez->mtrx + i*rez->columns) + j) = *((a.mtrx + i*a.columns) + j) + *((b.mtrx + i*b.columns) + j);
        }
    }
    return 0;
}
