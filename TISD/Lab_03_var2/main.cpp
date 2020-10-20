#include <iostream>
#include <list>

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
    int columns;
};

int sparse_matirx_calloc(sparse_matrix *m, int rows, int columns)
{
    m->mtrx_size = rows * columns;
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

    for (int i =0; i < m->columns; i++)
    {
        m->columns_id.push_back(-1);
    }

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

    for (int i = 0; i < m.columns; i++)
    {
        cout << *(m.mtrx + i) << " ";
    }
    cout << "\n" << endl;
}

int matrix_calloc(matrix *m, int rows, int columns)
{
    m->rows = rows;
    m->columns = columns;

    m->mtrx = new my_type [rows * columns];
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            *((m->mtrx + i*columns) + j) = i*columns + j + 1;// i*rows + j + 1
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

int main()
{
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

    sparse_matrix test;

    sparse_matirx_calloc(&test, 3, 4);
    print_sparse_matirx(test);

    matrix test1, test2, test3;

    matrix_calloc(&test1, 3, 4);
    matrix_calloc(&test2, 3, 4);
    matrix_calloc(&test3, 3, 4);
    print_matrix(test1);
    matrx_sum(test1, test2, &test3);
    print_matrix(test3);

    delete [] test1.mtrx;
    delete [] test2.mtrx;
    delete [] test3.mtrx;

    return 0;
}
