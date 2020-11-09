#include "defines.h"
#include "io_functions.h"
#include "mtrx_functions.h"

int main(int argc, char **argv)
{
    char file_name1[M] = "";
    char file_name2[M] = "";
    char rez_file_name[M] = "";
    int action_id = 0;
    //int n = 0;
    //int *mas = NULL;

    if (read_args(argc, argv, &action_id, file_name1, file_name2, rez_file_name) != 0)
        return CONSOLE_ARGS_ERROR;

    switch (action_id)
    {
        case 1:
        {
            double *mtrx1 = NULL;
            double **mtrx1_ptrs = NULL;
            int columns1 = 0, rows1 = 0;

            //printf("%p\n", mtrx1_ptrs);
            mtrx1_ptrs = read_mtrx_from_file(file_name1, mtrx1, &rows1, &columns1);
            //printf("%p\n", mtrx1_ptrs);
            if (mtrx1_ptrs == NULL)
            {
                return FILE_READ_ERROR;
            }
            //print_mtrx(mtrx1_ptrs, rows1, columns1);

            double *mtrx2 = NULL;
            double **mtrx2_ptrs = NULL;
            int columns2 = 0, rows2 = 0;
            mtrx2_ptrs = read_mtrx_from_file(file_name2, mtrx2, &rows2, &columns2);
            if (mtrx2_ptrs == NULL)
            {
                free(mtrx1);
                free(mtrx1_ptrs);
                return FILE_READ_ERROR;
            }

            if (columns1 != columns2 || rows1 != rows2)
            {
                free(mtrx1);
                free(mtrx1_ptrs);
                free(mtrx2);
                free(mtrx2_ptrs);
                return ADDITION_ERROR;
            }

            double *rez_mtrx = NULL;
            double **rez_mtrx_ptrs = NULL;
            rez_mtrx_ptrs = matrix_malloc(rez_mtrx, rows1, columns1);
            if (rez_mtrx_ptrs == NULL)
            {
                free(mtrx1);
                free(mtrx1_ptrs);
                free(mtrx2);
                free(mtrx2_ptrs);
                return ALLOC_ERROR;
            }

            mtrx_addition(mtrx1_ptrs, mtrx2_ptrs, rez_mtrx_ptrs, rows1, columns1);
            print_mtrx(mtrx1_ptrs, rows1, columns1);
            print_mtrx(mtrx2_ptrs, rows2, columns2);
            print_mtrx(rez_mtrx_ptrs, rows1, columns1);
            output_rez(rez_file_name, rez_mtrx_ptrs, rows1, columns1);

            free(mtrx1);
            free(mtrx1_ptrs);
            free(mtrx2);
            free(mtrx2_ptrs);
            free(rez_mtrx);
            free(rez_mtrx_ptrs);

            break;
        }
        case 2:
        {
            double *mtrx1 = NULL;
            double **mtrx1_ptrs = NULL;
            int columns1 = 0, rows1 = 0;

            mtrx1_ptrs = read_mtrx_from_file(file_name1, mtrx1, &rows1, &columns1);
            if (mtrx1_ptrs == NULL)
            {
                return FILE_READ_ERROR;
            }

            double *mtrx2 = NULL;
            double **mtrx2_ptrs = NULL;
            int columns2 = 0, rows2 = 0;
            mtrx2_ptrs = read_mtrx_from_file(file_name2, mtrx2, &rows2, &columns2);
            if (mtrx2_ptrs == NULL)
            {
                free(mtrx1);
                free(mtrx1_ptrs);
                return FILE_READ_ERROR;
            }

            if (columns1 != rows2)
            {
                free(mtrx1);
                free(mtrx1_ptrs);
                free(mtrx2);
                free(mtrx2_ptrs);
                return COMPOSITION_ERROR;
            }

            int rows = 0, columns = 0;
            if ((rows1 >= rows2))
                rows = rows1;
            else
                rows = rows2;

            if ((columns1 >= columns2))
                columns = columns1;
            else
                columns = columns2;

            double *rez_mtrx = NULL;
            double **rez_mtrx_ptrs = NULL;
            rez_mtrx_ptrs = matrix_malloc(rez_mtrx, rows, columns);
            if (rez_mtrx_ptrs == NULL)
            {
                free(mtrx1);
                free(mtrx1_ptrs);
                free(mtrx2);
                free(mtrx2_ptrs);
                return ALLOC_ERROR;
            }

            mtrx_composition(mtrx1_ptrs, mtrx2_ptrs, rez_mtrx_ptrs, rows, columns, columns1);

            output_rez(rez_file_name, rez_mtrx_ptrs, rows, columns);

            free(mtrx1);
            free(mtrx1_ptrs);
            free(mtrx2);
            free(mtrx2_ptrs);
            free(rez_mtrx);
            free(rez_mtrx_ptrs);

            break;
        }
        case 3:
        {
            double *mtrx = NULL;
            double **mtrx_ptrs = NULL;
            int columns = 0, rows = 0;

            mtrx_ptrs = read_mtrx_from_file(file_name1, mtrx, &rows, &columns);
            if (mtrx_ptrs == NULL)
            {
                return FILE_READ_ERROR;
            }
            if (rows != columns - 1)
            {
                free(mtrx);
                free(mtrx_ptrs);
                return COMPOSITION_ERROR;
            }
            //print_mtrx(mtrx_ptrs, rows, columns);

            double *rez_mtrx = NULL;
            double **rez_mtrx_ptrs = NULL;
            //rez_mtrx_ptrs = matrix_malloc(rez_mtrx, rows, 1);
            rez_mtrx_ptrs = solve_mtrx(mtrx_ptrs, rows, columns, rez_mtrx);

            output_solvation(rez_file_name, rez_mtrx_ptrs, rows);

            free(mtrx);
            free(mtrx_ptrs);
            free(rez_mtrx);
            free(rez_mtrx_ptrs);

            break;
        }
        default:
        {
            return CONSOLE_ARGS_ERROR;
            break;
        }
    }
    return 0;
}