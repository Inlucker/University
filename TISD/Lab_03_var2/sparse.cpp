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

    //here solved? Guess so yes!
    int *tmp1 = new int  [rez->rows * rez->columns];

    for (int i = 0; i < rez->rows * rez->columns; i++)
    {
        *(tmp1 + i) = 0;
    }

    int i = 0;
    int k = 0;
    int j = a.mtrx_id[i];
    list <int> :: iterator it = a.columns_id.begin();
    int tmp_i = 0;

    while (i < a.mtrx_size)
    {
        while (*it == -1 && k + tmp_i < a.columns - 1)
        {
            it++;
            tmp_i++;
        }
        if (i == *it)
        {
            k += tmp_i;
            tmp_i = 1;
            it++;
        }
        *((tmp1 + k * a.rows) + j) = i + 1;
        i++;
        j = a.mtrx_id[i];

    }

    /*for (int i = 0; i < rez->rows * rez->columns; i++)
    {
        cout << *(tmp1 + i) << " ";
    }
    cout << endl;*/

    int *tmp2 = new int  [rez->rows * rez->columns];

    for (int i = 0; i < rez->rows * rez->columns; i++)
    {
        *(tmp2 + i) = 0;
    }

    i = 0;
    k = 0;
    j = b.mtrx_id[i];
    it = b.columns_id.begin();
    tmp_i = 0;

    while (i < b.mtrx_size)
    {
        while (*it == -1 && k + tmp_i < b.columns - 1)
        {
            it++;
            tmp_i++;
        }
        if (i == *it)
        {
            k += tmp_i;
            tmp_i = 1;
            it++;
        }
        *((tmp2 + k * b.rows) + j) = i + 1;
        i++;
        j = b.mtrx_id[i];

    }

    /*for (int i = 0; i < rez->rows * rez->columns; i++)
    {
        cout << *(tmp2 + i) << " ";
    }
    cout << endl;*/

    //If upper works
    int rez_elems_amount = 0;
    for (int i = 0; i < rez->rows * rez->columns; i++)
    {
        if (*(tmp1 + i) != 0 || *(tmp2 + i) != 0)
            rez_elems_amount++;
    }

    sparse_matirx_calloc(rez, rez->rows, rez->columns, rez_elems_amount);

    j = 0;
    for (int i = 0; i < rez->rows * rez->columns; i++)
    {
        //cout << *(a.mtrx + *(tmp1 + i) - 1) << " " << *(b.mtrx + *(tmp2 + i) - 1) << " " << *(a.mtrx + *(tmp1 + i) - 1) + *(b.mtrx + *(tmp2 + i) - 1) << endl;
        //cout << *(tmp1 + i) << " " << *(tmp2 + i) << endl;
        //cout << endl;
        if (*(tmp1 + i) != 0 && *(tmp2 + i) != 0)
        {
            *(rez->mtrx + j) = *(a.mtrx + *(tmp1 + i) - 1) + *(b.mtrx + *(tmp2 + i) - 1);
            *(rez->mtrx_id + j) = *(a.mtrx_id + *(tmp1 + i) - 1);
            j++;
        }
        else if (*(tmp1 + i) != 0)
        {
            *(rez->mtrx + j) = *(a.mtrx + *(tmp1 + i) - 1);
            *(rez->mtrx_id + j) = *(a.mtrx_id + *(tmp1 + i) - 1);
            j++;
        }
        else if (*(tmp2 + i) != 0)
        {
            *(rez->mtrx + j) = *(b.mtrx + *(tmp2 + i) - 1);
            *(rez->mtrx_id + j) = *(b.mtrx_id + *(tmp2 + i) - 1);
            j++;
        }
    }

    //not working?
    //list <int> :: iterator a_it = a.columns_id.begin();
    //list <int> :: iterator b_it = b.columns_id.begin();
    /*for (list <int> :: iterator i = rez->columns_id.begin(); i != rez->columns_id.end(); ++i)
    {
        if (*a_it == -1 && *b_it == -1)
            *i = -1;
        else if (*a_it == -1)
            *i = *b_it;
        else if (*b_it == -1)
            *i = *a_it;
        else
            *i = min(*a_it, *b_it);
        a_it++;
        b_it++;
    }*/

    //I think this works
    it = rez->columns_id.begin();
    int tmp = 0;
    bool flag = true;
    for (int i = 0; i < rez->columns; i++)
    {
        for (int j = 0; j < rez->rows; j++)
        {
            //cout << "tmp_id: " << i*rez->rows + j << " value1: " << *(tmp1 + i*rez->rows + j) << "; value2: " << *(tmp2 + i*rez->rows + j) << endl;
            if (*(tmp1 + i*rez->rows + j) != 0 || *(tmp2 + i*rez->rows + j) != 0)
            {
                if (flag)
                {
                    *it = tmp;
                    it++;
                    flag = false;
                }
                tmp++;
            }
        }
        if (flag)
            it++;
        else
            flag = true;
    }

    delete [] tmp1;
    delete [] tmp2;

    return 0;
}
