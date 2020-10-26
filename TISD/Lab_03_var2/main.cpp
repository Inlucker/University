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
    gen_matrix(&test1, test1.rows, test1.columns, 25);

    matrix_calloc(&test2, starting_rows, starting_columns);
    gen_matrix(&test2, test2.rows, test2.columns, 50);

    matrix_calloc(&test3, starting_rows, starting_columns);
    matrx_sum(test1, test2, &test3);

    sparse_matrix sparse1, sparse2, sparse3;

    sparse_matirx_calloc(&sparse1, starting_rows, starting_columns, get_elems_amount(test1));
    fill_sparse_matrix(&sparse1, test1);

    sparse_matirx_calloc(&sparse2, starting_rows, starting_columns, get_elems_amount(test2));
    fill_sparse_matrix(&sparse2, test2);

    sparse_matirx_calloc(&sparse3, starting_rows, starting_columns, get_elems_amount(test3));
    fill_sparse_matrix(&sparse3, test3);

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
        cout << "5 - calculate addition into matrix 3 and print it in sparse form" << endl;
        cout << "6 - Time tests" << endl;
        /*cout << "6 - Print key_list" << endl;
        cout << "7 - Print car_list using key_list" << endl;
        cout << "8 - BubbleSort car_list by field" << endl;
        cout << "9 - BubbleSort price_key_list" << endl;
        cout << "10 - QuickSort price_key_list" << endl;
        cout << "11 - QuickSort car_list by field" << endl;
        cout << "12 - Time Tests for sorts" << endl;*/
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
            cout << "Enter rows (<=10 000): " << endl;
            int rows = 0;
            cin >> rows;
            if (rows > 10000 || rows < 0)
            {
                cout << "Wrong input" << endl;
                break;
            }

            _flushall();
            cout << "Enter columns (<=10 000): " << endl;
            int columns = 0;
            cin >> columns;
            if (columns > 10000 || columns < 0)
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
                cout << "Error calloc" << endl;
                break;
            }
            if (gen_matrix(&test1, rows, columns, percent) == 0 && gen_matrix(&test2, rows, columns, percent) == 0)
            {
                delete_sparse_matirx(&sparse1);
                sparse_matirx_calloc(&sparse1, rows, columns, get_elems_amount(test1));
                fill_sparse_matrix(&sparse1, test1);

                delete_sparse_matirx(&sparse2);
                sparse_matirx_calloc(&sparse2, rows, columns, get_elems_amount(test2));
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
            //Not yet
            cout << "Input sparse matrix" << endl;
            break;
        }
        case 5:
        {
            delete_sparse_matirx(&sparse3);
            delete_matirx(&test3);

            if (matrix_calloc(&test3, test1.rows, test1.columns))
            {
                cout << "Calloc error" << endl;
                break;
            }
            if (matrx_sum(test1, test2, &test3))
            {
                cout << "Addition error" << endl;
                break;
            }

            if (sparse_matrx_sum(sparse1, sparse2, &sparse3))
            {
                cout << "Addition error" << endl;
                break;
            }
            cout << "Calculation is done:" << endl;
            print_sparse_matirx(sparse3);
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
