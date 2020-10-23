/*#include <iostream>
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

struct sparse_matrix
{
    my_type *mtrx;
    int *mtrx_id;
    list <int> columns_id;
    int mtrx_size;
    int rows; //?
    int columns;
};

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
        *(m->mtrx + i) = 1;
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
        isFirst = true;
    }
    return 0;
}*/

#include "structs.h"
#include "matrix.h"
#include "sparse.h"

/*int gen_matrix(matrix *m, int rows, int columns, int percent)
{
    if (percent <= 0 || percent > 100 || rows <= 0 || columns <= 0)
        return ERROR;

    int elems_amount = (rows * columns * percent) / 100;

    int cur_el_number = 0;

    m->rows = rows;
    m->columns = columns;

    while (cur_el_number < elems_amount)
    {
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                if (rand() % 2 == 1)
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
}*/

/*int gen_sparse_matrix(sparse_matrix *m, int rows, int columns, int percent)
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
}*/

/*int matrix_calloc(matrix *m, int rows, int columns)
{
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
}*/

/*void print_matrix(matrix m)
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
}*/

/*void matrx_sum(matrix a, matrix b, matrix *rez)
{
    for (int i = 0; i < rez->rows; i++)
    {
        for (int j = 0; j < rez->columns; j++)
        {
            *((rez->mtrx + i*rez->columns) + j) = *((a.mtrx + i*a.columns) + j) + *((b.mtrx + i*b.columns) + j);
        }
    }
}*/

int main()
{
    srand(time(0));
    /*my_type A[16] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11, 12, 13, 14, 15, 16};
    int IA[16] = {0, 0, 0, 0, 1, 1, 1, 1, 2, 2, 2, 2, 3, 3, 3, 3};
    int JA[4] = {0, 1, 2, 3};

    my_type B[16] = {1, 5, 9, 13, 2, 6, 10, 14, 3, 7, 11, 15, 4, 8, 12, 16};
    int IB[16] = {0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3, 0, 1, 2, 3};
    int JB[4] = {0, 4, 8, 12};

    my_type R[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int IR[16] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int JR[4] = {0, 0, 0, 0};
    for (int i = 0; i < 4; i++)
    {
        for (int j = 0; j < 4; j++)
        {
            cout << A[IA[JA[i]]] << " "; //
        }
        cout << endl;
    }*/


    //gen_sparse_matrix(&test, 3, 4, 17);

    matrix test1, test2, test3;

    matrix_calloc(&test1, 3, 4);
    gen_matrix(&test1, 3, 4, 50);
    print_matrix(test1);

    matrix_calloc(&test2, 3, 4);
    gen_matrix(&test2, 3, 4, 17);
    print_matrix(test2);

    matrix_calloc(&test3, 3, 4);
    matrx_sum(test1, test2, &test3);
    //print_matrix(test3);



    sparse_matrix test;
    sparse_matirx_calloc(&test, test3.rows, test3.columns, get_elems_amount(test3));
    fill_sparse_matrix(&test, test3);
    //print_sparse_matirx(test);

    sparse_matrix sparse1, sparse2, sparse3;
    sparse_matirx_calloc(&sparse1, test1.rows, test1.columns, get_elems_amount(test1));
    fill_sparse_matrix(&sparse1, test1);
    print_sparse_matirx(sparse1);

    sparse_matirx_calloc(&sparse2, test2.rows, test2.columns, get_elems_amount(test2));
    fill_sparse_matrix(&sparse2, test2);
    print_sparse_matirx(sparse2);

    sparse_matrx_sum(sparse1, sparse2, &sparse3);

    print_sparse_matirx(sparse3);

    delete_sparse_matirx(&test);
    delete_sparse_matirx(&sparse1);
    delete_sparse_matirx(&sparse2);
    delete_sparse_matirx(&sparse3);

    delete_matirx(&test1);
    delete_matirx(&test2);
    delete_matirx(&test3);

    return 0;
}
