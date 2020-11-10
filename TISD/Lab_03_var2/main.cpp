#include "structs.h"
#include "matrix.h"
#include "sparse.h"

int main()
{
    cout << "Hi" << endl;
    srand(time(0));

    matrix test1, test2, test3;

    int starting_rows = 3;
    int starting_columns = 4;
    matrix_calloc(&test1, starting_rows, starting_columns);
    gen_matrix(&test1, test1.rows, test1.columns, 40);

    matrix_calloc(&test2, starting_rows, starting_columns);
    gen_matrix(&test2, test2.rows, test2.columns, 40);

    matrix_calloc(&test3, starting_rows, starting_columns);
    matrx_sum(test1, test2, &test3);

    sparse_matrix sparse1, sparse2, sparse3;

    sparse_matrix_calloc(&sparse1, starting_columns, get_elems_amount(test1));
    fill_sparse_matrix(&sparse1, test1);

    sparse_matrix_calloc(&sparse2, starting_columns, get_elems_amount(test2));
    fill_sparse_matrix(&sparse2, test2);

    sparse_matrix_calloc(&sparse3, starting_columns, get_elems_amount(test3));
    fill_sparse_matrix(&sparse3, test3);

    /*clock_t start = clock();
    //int cur_row = 0;
    int a_id = 0;
    //list <int> :: iterator a_it = sparse1.columns_id.begin();
    int b_id = 0;
    //list <int> :: iterator b_it = sparse2.columns_id.begin();
    int rez_id = 0;
    list <int> :: iterator rez_it = sparse3.columns_id.begin();
    //bool is_first = true;

    //cout << get_elems_amount(test3) << endl;
    while (rez_id < sparse3.mtrx_size)
    {
        if (a_id < sparse1.mtrx_size && b_id < sparse2.mtrx_size)
        {
            *(sparse3.mtrx + rez_id) = *(sparse1.mtrx + a_id) + *(sparse2.mtrx + b_id);
            *(sparse3.mtrx_id + rez_id) = *(sparse1.mtrx_id + a_id);
            a_id++;
            b_id++;
            rez_id++;
        }
        else if (a_id < sparse1.mtrx_size)
        {
            *(sparse3.mtrx + rez_id) = *(sparse1.mtrx + a_id);
            *(sparse3.mtrx_id + rez_id) = *(sparse1.mtrx_id + a_id);
            a_id++;
            rez_id++;
        }
        else if (b_id < sparse2.mtrx_size)
        {
            *(sparse3.mtrx + rez_id) = *(sparse2.mtrx + b_id);
            *(sparse3.mtrx_id + rez_id) = *(sparse2.mtrx_id + b_id);
            b_id++;
            rez_id++;
        }
        else
        {
            *(sparse3.mtrx + rez_id) = *(sparse1.mtrx + a_id - 1);
            *(sparse3.mtrx_id + rez_id) = *(sparse1.mtrx_id + a_id - 1);
            rez_id++;
        }
    }
    for (list <int> :: iterator i = sparse3.columns_id.begin(); i != sparse3.columns_id.end(); ++i)
    {
        *i = 0;
    }
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Time: %.4f seconds\n", seconds);

    fill_sparse_matrix(&sparse3, test3);*/



    //memory_calculating(3, 4, 50);

    /*cout << "sparse3: " << endl;
    print_sparse_matirx(sparse3);
    cout << "sparse1: " << endl;
    print_sparse_matirx(sparse1);
    cout << "sparse2: " << endl;
    print_sparse_matirx(sparse2);
    cout << "test1: " << endl;
    print_matrix(test1);
    cout << "test2: " << endl;
    print_matrix(test2);

    delete_sparse_matirx(&sparse3);
    sparse_matrix_calloc(&sparse3, starting_columns, get_elems_amount(test3));
    sparse_matrx_sum2(sparse1, sparse2, &sparse3);
    print_sparse_matirx(sparse3);*/

    /*print_sparse_matirx(sparse3);

    delete_sparse_matirx(&sparse3);
    sparse_matrx_sum(sparse1, sparse2, &sparse3);
    print_sparse_matirx(sparse3);*/

    int input = -1;

    //cout << sizeof (car) << " " << sizeof (price_keys) << endl;

    while (input != 0)
    {
        cout << endl;
        cout << "1 - Print default matrixes" << endl;
        cout << "2 - Print sparse matrixes" << endl;
        cout << "3 - Generate matrixes" << endl;
        cout << "4 - Input sparse matrix" << endl;
        cout << "5 - calculate addition into matrix 3" << endl; //<< " and print it in sparse form" << endl;
        cout << "6 - Time tests" << endl;
        cout << "7 - Memory calculating" << endl;
        cout << "0 - Exit from programm" << endl;
        cout << endl;

        _flushall();
        cout << "Enter the number of command to be done: ";
        while (!(cin >> input))
        {
            cout << "Wrong input" << endl;
            cin.clear();
            _flushall();
            cout << "Enter the number of command to be done: ";
        }

        switch (input)
        {
        case 1:
        {
            cout << "matrix1:" << endl;
            print_matrix(test1);
            cout << "matrix2:" << endl;
            print_matrix(test2);
            cout << "matrix3:" << endl;
            print_matrix(test3);
            break;
        }
        case 2:
        {
            cout << "matrix1:" << endl;
            print_sparse_matirx(sparse1);
            cout << "matrix2:" << endl;
            print_sparse_matirx(sparse2);
            cout << "matrix3:" << endl;
            print_sparse_matirx(sparse3);
            break;
        }
        case 3:
        {
            _flushall();
            cout << "Enter rows (<=5 000): " << endl;
            int rows = 0;
            cin >> rows;
            if (rows > 5000 || rows <= 0)
            {
                cout << "Wrong input" << endl;
                break;
            }

            _flushall();
            cout << "Enter columns (<=5 000): " << endl;
            int columns = 0;
            cin >> columns;
            if (columns > 5000 || columns <= 0)
            {
                cout << "Wrong input" << endl;
                break;
            }

            _flushall();
            cout << "Enter the percentage of generation (1 - 100): " << endl;
            int percent = 0;
            cin >> percent;
            if (percent > 100 || percent <= 0)
            {
                cout << "Wrong input" << endl;
                break;
            }

            delete_matirx(&test1);
            delete_matirx(&test2);

            if  (matrix_calloc(&test1, rows, columns) != 0 || matrix_calloc(&test2, rows, columns) != 0)
            {
                cout << "Error alloc" << endl;
                break;
            }
            if (gen_matrix(&test1, rows, columns, percent) == 0 && gen_matrix(&test2, rows, columns, percent) == 0)
            {
                delete_sparse_matirx(&sparse1);
                sparse_matrix_calloc(&sparse1, columns, get_elems_amount(test1));
                fill_sparse_matrix(&sparse1, test1);

                delete_sparse_matirx(&sparse2);
                sparse_matrix_calloc(&sparse2, columns, get_elems_amount(test2));
                fill_sparse_matrix(&sparse2, test2);
            }
            else
            {
                cout << "Wrong input" << endl;
                break;
            }
            break;
        }
        case 4:
        {
            sparse_matrix sparse;
            matrix test;

            _flushall();
            cout << "Enter rows (<=5 000): " << endl;
            int rows = 0;
            cin >> rows;
            if (rows > 5000 || rows <= 0)
            {
                cout << "Wrong input" << endl;
                break;
            }

            _flushall();
            cout << "Enter columns (<=5 000): " << endl;
            int columns = 0;
            cin >> columns;
            if (columns > 5000 || columns <= 0)
            {
                cout << "Wrong input" << endl;
                break;
            }

            _flushall();
            cout << "Enter the number of non-zero elements (<= rows * columns): " << endl;
            int elems_amount = 0;
            cin >> elems_amount;
            if (elems_amount > rows * columns || elems_amount <= 0)
            {
                cout << "Wrong input" << endl;
                break;
            }

            if (sparse_matrix_calloc(&sparse, columns, elems_amount))
            {
                cout << "Alloc error" << endl;
                break;
            }

            if (matrix_calloc(&test, rows, columns))
            {
                cout << "Alloc error" << endl;
                delete_sparse_matirx(&sparse);
                break;
            }

            _flushall();
            cout << "Enter mtrx:" << endl;
            for (int i = 0; i < elems_amount; i++)
            {
                int input;
                while (!(cin >> input))
                {
                    cin.clear();
                    _flushall();
                    cout << "Wrong input, try again (current i = " << i << ")" << endl;
                }
                *(sparse.mtrx + i) = input;
            }

            _flushall();
            cout << "Enter mtrx_id:" << endl;
            for (int i = 0; i < elems_amount; i++)
            {
                int input;
                while (!(cin >> input) || input >= rows)
                {
                    cin.clear();
                    _flushall();
                    cout << "Wrong input (should be < " << rows << "), try again (current i = " << i << ")" << endl;
                }
                *(sparse.mtrx_id + i) = input;
            }

            _flushall();
            cout << "Enter columns_id (-1 if it has no non-zero elements):" << endl;
            //int prev_input = -2;
            for (list <int> :: iterator i = sparse.columns_id.begin(); i != sparse.columns_id.end(); ++i)
            {
                int input;// = -2;
                //prev_input = input;
                while (!(cin >> input))// || input >= elems_amount || (input <= prev_input && input != -1))
                {
                    cin.clear();
                    _flushall();
                    cout << "Wrong input, try again" << endl;
                }
                *i = input;
            }
            fill_matrix(&test, sparse);
            fill_sparse_matrix(&sparse, test);
            if (sparse.mtrx_size != elems_amount)
            {
                cout << "Wrong input" << endl;;
                delete_sparse_matirx(&sparse);
                delete_matirx(&test);
                break;
            }

            cout << "Sparse:" << endl;
            print_sparse_matirx(sparse);
            cout << "Default:" << endl;
            print_matrix(test);

            _flushall();
            cout << "Enter wich matrix it should be (1/2/3): " << endl;
            int tmp = 0;
            while (!(cin >> tmp) || tmp <= 0 || tmp > 3)// || input >= elems_amount || (input <= prev_input && input != -1))
            {
                cin.clear();
                _flushall();
                cout << "Wrong input, try again (1/2/3)" << endl;
            }

            switch (tmp)
            {
            case 1:
            {
                sparse1 = sparse;
                test1 = test;
                break;
            }
            case 2:
            {
                sparse2 = sparse;
                test2 = test;
                break;
            }
            case 3:
            {
                sparse3 = sparse;
                test3 = test;
                break;
            }
            default:
                cout << "Assign error" << endl;
                delete_sparse_matirx(&sparse);
                delete_matirx(&test);
                break;
            }

            //cout << "Input sparse matrix" << endl;
            break;
        }
        case 5:
        {
            delete_sparse_matirx(&sparse3);
            delete_matirx(&test3);

            if (matrix_calloc(&test3, test1.rows, test1.columns))
            {
                cout << "Alloc error" << endl;
                break;
            }
            if (matrx_sum(test1, test2, &test3))
            {
                cout << "Addition error" << endl;
                break;
            }

            if (sparse_matrix_calloc(&sparse3, test3.columns, get_elems_amount(test3)))
            {
                cout << "Alloc error" << endl;
                break;
            }
            //if (sparse_matrix_sum(sparse1, sparse2, &sparse3, test3.rows))
            //if (sparse_matrix_sum_last(sparse1, sparse2, &sparse3, get_elems_amount(test3)))
            if (sparse_matrix_sum4(sparse1, sparse2, &sparse3))
            {
                cout << "Addition error" << endl;
                break;
            }
            cout << "Calculation is done" << endl;
            //print_sparse_matirx(sparse3);
            break;
        }
        case 6:
        {
            _flushall();
            cout << "Enter rows (<=5 000): " << endl;
            int rows = 0;
            cin >> rows;
            if (rows > 5000 || rows <= 0)
            {
                cout << "Wrong input" << endl;
                break;
            }

            _flushall();
            cout << "Enter columns (<=5 000): " << endl;
            int columns = 0;
            cin >> columns;
            if (columns > 5000 || columns <= 0)
            {
                cout << "Wrong input" << endl;
                break;
            }

            _flushall();
            cout << "Enter the percentage of generation (1 - 100): " << endl;
            int percent = 0;
            cin >> percent;
            if (percent > 100 || percent <= 0)
            {
                cout << "Wrong input" << endl;
                break;
            }

            //recalloc and generating of 1-2 matrixes
            delete_matirx(&test1);
            delete_matirx(&test2);

            if  (matrix_calloc(&test1, rows, columns) != 0 || matrix_calloc(&test2, rows, columns) != 0)
            {
                cout << "Error alloc" << endl;
                break;
            }
            if (gen_matrix(&test1, rows, columns, percent) == 0 && gen_matrix(&test2, rows, columns, percent) == 0)
            {
                delete_sparse_matirx(&sparse1);
                sparse_matrix_calloc(&sparse1, columns, get_elems_amount(test1));
                fill_sparse_matrix(&sparse1, test1);

                delete_sparse_matirx(&sparse2);
                sparse_matrix_calloc(&sparse2, columns, get_elems_amount(test2));
                fill_sparse_matrix(&sparse2, test2);
            }
            else
            {
                cout << "Wrong input" << endl;
                break;
            }

            delete_sparse_matirx(&sparse3);
            delete_matirx(&test3);

            //Default addition test
            if (matrix_calloc(&test3, rows, columns))
            {
                cout << "Alloc error" << endl;
                break;
            }
            clock_t start = clock();
            if (matrx_sum(test1, test2, &test3))
            {
                cout << "Addition error" << endl;
                break;
            }
            clock_t end = clock();
            double seconds = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Default matrixes addition test time: %.4f seconds\n", seconds);

            //Sparse addition test
            //cout << test3.columns << " " << get_elems_amount(test3) << endl;
            if (sparse_matrix_calloc(&sparse3, columns, get_elems_amount(test3)))
            {
                cout << "Alloc error" << endl;
                break;
            }
            start = clock();
            //if (sparse_matrix_sum(sparse1, sparse2, &sparse3, rows))
            if (sparse_matrix_sum4(sparse1, sparse2, &sparse3))
            {
                cout << "Addition error" << endl;
                break;
            }
            end = clock();
            double sparse_seconds = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Sparse matrixes addition test time: %.4f seconds\n", sparse_seconds/6);
            break;
        }
        case 7:
        {
            _flushall();
            cout << "Enter rows (<=5 000): " << endl;
            int rows = 0;
            cin >> rows;
            if (rows > 5000 || rows <= 0)
            {
                cout << "Wrong input" << endl;
                break;
            }

            _flushall();
            cout << "Enter columns (<=5 000): " << endl;
            int columns = 0;
            cin >> columns;
            if (columns > 5000 || columns <= 0)
            {
                cout << "Wrong input" << endl;
                break;
            }

            _flushall();
            cout << "Enter the percentage of generation (1 - 100): " << endl;
            int percent = 0;
            cin >> percent;
            if (percent > 100 || percent <= 0)
            {
                cout << "Wrong input" << endl;
                break;
            }

            memory_calculating(rows, columns, percent);
            break;
        }
        case 0:
        {
            cout << "Good buy!" << endl;
            break;
        }
        default:
            cout << "Wrong command" << endl;
            break;
        }
    }

    delete_sparse_matirx(&sparse1);
    delete_sparse_matirx(&sparse2);
    delete_sparse_matirx(&sparse3);

    delete_matirx(&test1);
    delete_matirx(&test2);
    delete_matirx(&test3);

    return 0;
}
