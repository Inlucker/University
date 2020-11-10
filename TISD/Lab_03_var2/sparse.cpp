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

void fill_sparse_matrix(sparse_matrix *rez, matrix m)
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
}

/*int gen_sparse_matrix(sparse_matrix *m, int rows, int columns, int percent)
{
    if (percent <= 0 || percent > 100 || rows <= 0 || columns <= 0)
        return ERROR;
    int elems_amount = (rows * columns * percent) / 100;
    if (elems_amount <= 0 || elems_amount > rows * columns)
        return ERROR;
    sparse_matrix_calloc(m, columns, elems_amount);
    return 0;
}*/

void print_sparse_matirx(sparse_matrix m)
{
    if (m.mtrx_size != 0)
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
    else
    {
        cout << "No non-zero elemments" << endl;
    }
}

int sparse_matrix_sum_cheat(sparse_matrix a, sparse_matrix b, sparse_matrix *rez, int elems_amount)
{
    if (a.columns != b.columns && b.columns != rez->columns)
        return ERROR;
    rez->columns = a.columns;

    int cur_column = 0;
    int a_id = 0;
    list <int> :: iterator a_it = a.columns_id.begin();
    int *a_mas = new int[elems_amount];

    int b_id = 0;
    list <int> :: iterator b_it = b.columns_id.begin();
    int *b_mas = new int[elems_amount];

    int rez_id = 0;
    list <int> :: iterator rez_it = rez->columns_id.begin();

    while (cur_column < rez->columns)
    {
        int a_it_next_value = a.mtrx_size;
        if (next(a_it) != a.columns_id.end())
        {
            list <int> :: iterator a_it_next = next(a_it);
            while(*a_it_next == -1 && a_it_next != a.columns_id.end())
            {
                a_it_next++;
            }
            a_it_next_value = *a_it_next;
            if (a_it_next != b.columns_id.end())
                a_it_next_value = *a_it_next;
        }

        int b_it_next_value = b.mtrx_size;
        if (next(b_it) != b.columns_id.end())
        {
            list <int> :: iterator b_it_next = next(b_it);
            while(*b_it_next == -1 && b_it_next != b.columns_id.end())
            {
                b_it_next++;
            }
            if (b_it_next != b.columns_id.end())
                b_it_next_value = *b_it_next;
        }

        if (*a_it != -1 || *b_it != -1)
        {
            *rez_it = rez_id;
        }

        //cout << "a: "<< *next(a_it) << " b: " << *next(b_it) << endl;
        //cout << "cur_column: " << cur_column << "; rez_id - " << rez_id << endl;
        while(a.mtrx_size > a_id || b.mtrx_size > b_id)
        {
            //cout << "cur_column: " << cur_column << endl;
            //cout << a_id << " " << a_it_next_value << " " << b_id << " " << b_it_next_value << endl;

            //cout << *(a.mtrx_id + a_id) << " " << *(a.mtrx + a_id) << " " << *(b.mtrx_id + b_id) << " " << *(b.mtrx + b_id) << endl;

            if ((a_id == a_it_next_value && b_id == b_it_next_value) || (*a_it == -1 && *b_it == -1) || (a_id >= a.mtrx_size && b_id >= b.mtrx_size))
                break;

            if (*a_it != -1 && *b_it != -1)
            {
                if (a_id != a_it_next_value && b_id != b_it_next_value)
                {
                    if (*(a.mtrx_id + a_id) == *(b.mtrx_id + b_id))
                    {
                        a_mas[rez_id] = *(a.mtrx_id + a_id);
                        b_mas[rez_id] = *(b.mtrx_id + b_id);
                        rez_id++;
                        a_id++;
                        b_id++;
                    }
                    else if (*(a.mtrx_id + a_id) < *(b.mtrx_id + b_id))
                    {
                        a_mas[rez_id] = *(a.mtrx_id + a_id);
                        b_mas[rez_id] = -1;
                        rez_id++;
                        a_id++;
                    }
                    else if (*(a.mtrx_id + a_id) > *(b.mtrx_id + b_id))
                    {
                        a_mas[rez_id] = -1;
                        b_mas[rez_id] = *(b.mtrx_id + b_id);
                        rez_id++;
                        b_id++;
                    }
                    else
                        cout << "WORLD ERROR" << endl;
                }
                else if (a_id != a_it_next_value)
                {
                    a_mas[rez_id] = *(a.mtrx_id + a_id);
                    b_mas[rez_id] = -1;
                    rez_id++;
                    a_id++;
                }
                else if (b_id != b_it_next_value)
                {
                    a_mas[rez_id] = -1;
                    b_mas[rez_id] = *(b.mtrx_id + b_id);
                    rez_id++;
                    b_id++;
                }
                else
                    cout << "(INPUT_DATA_ERROR on rez_id = " << rez_id << endl;
            }
            else if (*a_it != -1)
            {
                a_mas[rez_id] = *(a.mtrx_id + a_id);
                b_mas[rez_id] = -1;
                rez_id++;
                a_id++;
            }
            else if (*b_it != -1)
            {
                a_mas[rez_id] = -1;
                b_mas[rez_id] = *(b.mtrx_id + b_id);
                rez_id++;
                b_id++;
            }
            else if (*a_it == -1 && *b_it == -1)
                break;
            else
                cout << "ERROR on rez_id = " << rez_id << endl;
        }
        cur_column++;
        rez_it++;
        a_it++;
        b_it++;
    }

    /*for (int i = 0; i < rez->mtrx_size; i++)
    {
        cout << a_mas[i] << " ";
    }
    cout << endl;

    for (int i = 0; i < rez->mtrx_size; i++)
    {
        cout << b_mas[i] << " ";
    }
    cout << endl;*/

    a_id = 0;
    b_id = 0;
    rez_id = 0;

    clock_t start = clock();

    while (rez_id <= rez->mtrx_size)
    {
        if (a_mas[rez_id] != -1 && b_mas[rez_id] != -1)
        {
            *(rez->mtrx + rez_id) = *(a.mtrx + a_id) + *(b.mtrx + b_id);
            *(rez->mtrx_id + rez_id) = *(a.mtrx_id + a_id);
            rez_id++;
            a_id++;
            b_id++;
        }
        else if (a_mas[rez_id] != -1)
        {
            *(rez->mtrx + rez_id) = *(a.mtrx + a_id);
            *(rez->mtrx_id + rez_id) = *(a.mtrx_id + a_id);
            rez_id++;
            a_id++;
        }
        else if (b_mas[rez_id] != -1)
        {
            *(rez->mtrx + rez_id) = *(b.mtrx + b_id);
            *(rez->mtrx_id + rez_id) = *(b.mtrx_id + b_id);
            rez_id++;
            b_id++;
        }
        else
        {
            cout << "Infinite iterations error" << endl;
            break;
        }
    }

    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Sparse matrixes addition(inside) test time: %.4f seconds\n", seconds);

    return 0;
}

int sparse_matrix_sum2(sparse_matrix a, sparse_matrix b, sparse_matrix *rez)
{
    if (a.columns != b.columns && b.columns != rez->columns)
        return ERROR;
    //rez->rows = a.rows;
    rez->columns = a.columns;


    int cur_row = 0;
    int cur_column = 0;
    int a_id = 0;
    list <int> :: iterator a_it = a.columns_id.begin();
    int b_id = 0;
    list <int> :: iterator b_it = b.columns_id.begin();
    int rez_id = 0;
    list <int> :: iterator rez_it = rez->columns_id.begin();
    bool is_first = true;

    while (cur_column < rez->columns)
    {
        list <int> :: iterator a_it_next = next(a_it);
        while(*a_it_next == -1 && a_it_next != a.columns_id.end())
        {
            a_it_next++;
        }
        list <int> :: iterator b_it_next = next(b_it);
        while(*b_it_next == -1 && b_it_next != b.columns_id.end())
        {
            b_it_next++;
        }
        while(a.mtrx_size > a_id || b.mtrx_size > b_id)
        {
            //cout << "cur_column: " << cur_column << endl;
            //cout << a_id << " " << *a_it_next << " " << b_id << " " << *b_it_next << endl;
            //cout << "cur_row: " << cur_row << endl;

            if (((a_id == *a_it_next || a.mtrx_size <= a_id) && (b_id == *b_it_next || b.mtrx_size <= b_id)) || (*a_it == -1 && *b_it == -1))
                break;

            if (*(a.mtrx_id + a_id) == cur_row && *a_it != -1 && a_id != *a_it_next)
            {
                //cout << "a: mtrx_id[a_id] - " << *(a.mtrx_id + a_id) << "; *a_it - " << *a_it << "; a_id - " << a_id << "; *next(a_it) - " << *next(a_it) << endl;
                *(rez->mtrx + rez_id) += *(a.mtrx + a_id);
                a_id++;
                if (is_first)
                {
                    *rez_it = rez_id;
                    is_first = false;
                }
            }
            if (*(b.mtrx_id + b_id) == cur_row && *b_it != -1 && b_id != *b_it_next)
            {
                //cout << "b: mtrx_id[b_id] - " << *(b.mtrx_id + b_id) << "; *b_it - " << *b_it << "; b_id - " << b_id << "; *next(b_it) - " << *next(b_it) << endl;
                *(rez->mtrx + rez_id) += *(b.mtrx + b_id);
                b_id++;
                if (is_first)
                {
                    *rez_it = rez_id;
                    is_first = false;
                }
            }
            if (*(rez->mtrx + rez_id) != 0)
            {
                *(rez->mtrx_id + rez_id) = cur_row;
                //cout << *(rez->mtrx + rez_id) << endl;
                rez_id++;
            }

            //if (rez_id >= rez->mtrx_size)
            if (a.mtrx_size <= a_id && b.mtrx_size <= b_id)
                break;
            cur_row++;
        }
        rez_it++;
        a_it++;
        b_it++;
        cur_row = 0;
        is_first = true;
        cur_column++;
    }

    return 0;
}

int sparse_matrix_sum4(sparse_matrix a, sparse_matrix b, sparse_matrix *rez) //works for sure
{
    //clock_t start = clock();

    if (a.columns != b.columns && b.columns != rez->columns)
        return ERROR;
    rez->columns = a.columns;

    //int cur_row = 0;
    int cur_column = 0;
    int a_id = 0;
    list <int> :: iterator a_it = a.columns_id.begin();
    int b_id = 0;
    list <int> :: iterator b_it = b.columns_id.begin();
    int rez_id = 0;
    list <int> :: iterator rez_it = rez->columns_id.begin();

    while (cur_column < rez->columns)
    {
        int a_it_next_value = a.mtrx_size;
        if (next(a_it) != a.columns_id.end())
        {
            list <int> :: iterator a_it_next = next(a_it);
            while(*a_it_next == -1 && a_it_next != a.columns_id.end())
            {
                a_it_next++;
            }
            a_it_next_value = *a_it_next;
            if (a_it_next != b.columns_id.end())
                a_it_next_value = *a_it_next;
        }

        int b_it_next_value = b.mtrx_size;
        if (next(b_it) != b.columns_id.end())
        {
            list <int> :: iterator b_it_next = next(b_it);
            while(*b_it_next == -1 && b_it_next != b.columns_id.end())
            {
                b_it_next++;
            }
            if (b_it_next != b.columns_id.end())
                b_it_next_value = *b_it_next;
        }

        if (*a_it != -1 || *b_it != -1)
        {
            *rez_it = rez_id;
        }

        //cout << "a: "<< *next(a_it) << " b: " << *next(b_it) << endl;
        //cout << "cur_column: " << cur_column << "; rez_id - " << rez_id << endl;
        while(a.mtrx_size > a_id || b.mtrx_size > b_id)
        {
            //cout << "cur_column: " << cur_column << endl;
            //cout << a_id << " " << a_it_next_value << " " << b_id << " " << b_it_next_value << endl;

            //cout << *(a.mtrx_id + a_id) << " " << *(a.mtrx + a_id) << " " << *(b.mtrx_id + b_id) << " " << *(b.mtrx + b_id) << endl;

            if ((a_id == a_it_next_value && b_id == b_it_next_value) || (*a_it == -1 && *b_it == -1) || (a_id >= a.mtrx_size && b_id >= b.mtrx_size))
                break;

            if (*a_it != -1 && *b_it != -1)
            {
                if (a_id != a_it_next_value && b_id != b_it_next_value)
                {
                    if (*(a.mtrx_id + a_id) == *(b.mtrx_id + b_id))
                    {
                        *(rez->mtrx + rez_id) = *(a.mtrx + a_id) + *(b.mtrx + b_id);
                        *(rez->mtrx_id + rez_id) = *(a.mtrx_id + a_id);
                        rez_id++;
                        a_id++;
                        b_id++;
                    }
                    else if (*(a.mtrx_id + a_id) < *(b.mtrx_id + b_id))
                    {
                        *(rez->mtrx + rez_id) = *(a.mtrx + a_id);
                        *(rez->mtrx_id + rez_id) = *(a.mtrx_id + a_id);
                        rez_id++;
                        a_id++;
                    }
                    else if (*(a.mtrx_id + a_id) > *(b.mtrx_id + b_id))
                    {
                        *(rez->mtrx + rez_id) = *(b.mtrx + b_id);
                        *(rez->mtrx_id + rez_id) = *(b.mtrx_id + b_id);
                        rez_id++;
                        b_id++;
                    }
                    else
                        cout << "WORLD ERROR" << endl;
                }
                else if (a_id != a_it_next_value)
                {
                    *(rez->mtrx + rez_id) = *(a.mtrx + a_id);
                    *(rez->mtrx_id + rez_id) = *(a.mtrx_id + a_id);
                    rez_id++;
                    a_id++;
                }
                else if (b_id != b_it_next_value)
                {
                    *(rez->mtrx + rez_id) = *(b.mtrx + b_id);
                    *(rez->mtrx_id + rez_id) = *(b.mtrx_id + b_id);
                    rez_id++;
                    b_id++;
                }
                else
                    cout << "(INPUT_DATA_ERROR on rez_id = " << rez_id << endl;
            }
            else if (*a_it != -1)
            {
                *(rez->mtrx + rez_id) = *(a.mtrx + a_id);
                *(rez->mtrx_id + rez_id) = *(a.mtrx_id + a_id);
                rez_id++;
                a_id++;
            }
            else if (*b_it != -1)
            {
                *(rez->mtrx + rez_id) = *(b.mtrx + b_id);
                *(rez->mtrx_id + rez_id) = *(b.mtrx_id + b_id);
                rez_id++;
                b_id++;
            }
            else if (*a_it == -1 && *b_it == -1)
                break;
            else
                cout << "ERROR on rez_id = " << rez_id << endl;
        }
        cur_column++;
        rez_it++;
        a_it++;
        b_it++;
    }

    /*clock_t end = clock();
    double sparse_seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Sparse matrixes addition(inside) test time: %.4f seconds\n", sparse_seconds/6);*/

    return 0;
}

//STUPID FUNCTION FOR NOTHING
/*void fill_columns_id(sparse_matrix *m)
{
    list <int> :: iterator it = m->columns_id.begin();
    int i = 0;
    while (i < m->mtrx_size)
    {
        while (*it == -1)
        {
            it++;
        }
        *it = i;
        it++;
        while (*it == -1)
        {
            it++;
        }
        cout << *it << endl;
        while (i != *it && i < m->mtrx_size)
        {
            i++;
        }
    }
}*/

int sparse_matrix_sum(sparse_matrix a, sparse_matrix b, sparse_matrix *rez, int rows)
{
    if (a.columns != b.columns)
        return ERROR;
    //rez->rows = a.rows;
    rez->columns = a.columns;

    //here solved? Guess so yes!
    int *tmp1 = new int  [rows * rez->columns];

    for (int i = 0; i < rows * rez->columns; i++)
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
        *((tmp1 + k * rows) + j) = i + 1;
        i++;
        j = a.mtrx_id[i];

    }


    int *tmp2 = new int  [rows * rez->columns];

    for (int i = 0; i < rows * rez->columns; i++)
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
        *((tmp2 + k * rows) + j) = i + 1;
        i++;
        j = b.mtrx_id[i];

    }

    //If upper works
    int rez_elems_amount = 0;
    for (int i = 0; i < rows * rez->columns; i++)
    {
        if (*(tmp1 + i) != 0 || *(tmp2 + i) != 0)
            rez_elems_amount++;
    }

    if (sparse_matrix_calloc(rez, rez->columns, rez_elems_amount))
        return ERROR;

    clock_t start = clock();
    j = 0;
    for (int i = 0; i < rows * rez->columns; i++)
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

    //I think this works
    it = rez->columns_id.begin();
    int tmp = 0;
    bool flag = true;
    for (int i = 0; i < rez->columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            //cout << "tmp_id: " << i*rez->rows + j << " value1: " << *(tmp1 + i*rez->rows + j) << "; value2: " << *(tmp2 + i*rez->rows + j) << endl;
            if (*(tmp1 + i* + j) != 0 || *(tmp2 + i* + j) != 0)
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
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Sparse matrixes addition test time: %.4f seconds\n", seconds);

    delete [] tmp1;
    delete [] tmp2;

    return 0;
}

//Оказалось sh*t idea
/*int sparse_matrix_sum3(sparse_matrix a, sparse_matrix b, sparse_matrix *rez)
{
    if (a.columns != b.columns && b.columns != rez->columns)
        return ERROR;

    rez->columns = a.columns;

    //int current_row = 0;
    int cur_column = 0;
    int a_id = 0;
    list <int> :: iterator a_it = a.columns_id.begin();
    int b_id = 0;
    list <int> :: iterator b_it = b.columns_id.begin();
    int rez_id = 0;
    list <int> :: iterator rez_it = rez->columns_id.begin();
    //bool is_first = true;

    while (cur_column < rez->columns)
    {
        list <int> :: iterator a_it_next = next(a_it);
        while(*a_it_next == -1 && a_it_next != a.columns_id.end())
        {
            a_it_next++;
        }
        list <int> :: iterator b_it_next = next(b_it);
        while(*b_it_next == -1 && b_it_next != b.columns_id.end())
        {
            b_it_next++;
        }

        //cout << "a: "<< *next(a_it) << " b: " << *next(b_it) << endl;
        //cout << "cur_column: " << cur_column << "; rez_id - " << rez_id << endl;
        if (*a_it != -1 || *b_it != -1)
        {
            *rez_it = rez_id;
        }

        while(a.mtrx_size > a_id || b.mtrx_size > b_id)
        {
            //cout << "cur_column: " << cur_column << endl;
            //cout << a_id << " " << *a_it_next << " " << b_id << " " << *b_it_next << endl;

            if (((a_id == *a_it_next || a.mtrx_size <= a_id) && (b_id == *b_it_next || b.mtrx_size <= b_id) && cur_column != rez->columns - 1)
                    || (a.mtrx_size <= a_id && b.mtrx_size <= b_id && cur_column == rez->columns - 1)
                    || (*a_it == -1 && *b_it == -1))
                break;

            if ((*a_it != -1 && *b_it != -1 && a_id != *a_it_next && b_id != *b_it_next) || cur_column == rez->columns - 1)
            {
                if (*(a.mtrx_id + a_id) > *(b.mtrx_id + b_id))
                {
                    *(rez->mtrx + rez_id) = *(b.mtrx + b_id);
                    *(rez->mtrx_id + rez_id) = *(b.mtrx_id + b_id);
                    b_id++;
                }
                else if (*(a.mtrx_id + a_id) < *(b.mtrx_id + b_id))
                {
                    *(rez->mtrx + rez_id) = *(a.mtrx + a_id);
                    *(rez->mtrx_id + rez_id) = *(a.mtrx_id + a_id);
                    a_id++;
                }
                else
                {
                    *(rez->mtrx + rez_id) = *(a.mtrx + a_id) + *(b.mtrx + b_id);
                    *(rez->mtrx_id + rez_id) = *(a.mtrx_id + a_id);
                    a_id++;
                    b_id++;
                }

                rez_id++;
            }
            else if (*a_it != -1 && a_id != *a_it_next)
            {
                *(rez->mtrx + rez_id) = *(a.mtrx + a_id);
                *(rez->mtrx_id + rez_id) = *(a.mtrx_id + a_id);
                rez_id++;
                a_id++;
            }
            else if (*b_it != -1 && b_id != *b_it_next)
            {
                *(rez->mtrx + rez_id) =*(b.mtrx + b_id);
                *(rez->mtrx_id + rez_id) = *(b.mtrx_id + b_id);
                rez_id++;
                b_id++;
            }
            else
                break;


            //if (rez_id >= rez->mtrx_size)
        }
        rez_it++;
        a_it++;
        b_it++;
        //is_first = true;
        cur_column++;
    }

    return 0;
}*/

