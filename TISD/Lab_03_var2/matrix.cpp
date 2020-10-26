#include "matrix.h"

int gen_matrix(matrix *m, int rows, int columns, int percent)
{
    if (percent <= 0 || percent > 100 || rows <= 0 || columns <= 0)
        return ERROR;

    int elems_amount = (rows * columns * percent) / 100;
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

void print_matrix(matrix m)
{
    for (int i = 0; i < m.rows; i++)
    {
        for (int j = 0; j < m.columns; j++)
        {
            cout << *((m.mtrx + i * m.columns) + j) << " ";
        }
        cout << endl;
    }
    cout << endl;
}

void matrx_sum(matrix a, matrix b, matrix *rez)
{
    for (int i = 0; i < rez->rows; i++)
    {
        for (int j = 0; j < rez->columns; j++)
        {
            *((rez->mtrx + i*rez->columns) + j) = *((a.mtrx + i*a.columns) + j) + *((b.mtrx + i*b.columns) + j);
        }
    }
}
