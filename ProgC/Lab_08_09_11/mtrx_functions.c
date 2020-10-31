#include "mtrx_functions.h"


double** matrix_malloc(double *mtrx, int rows, int columns)
{
    double** mtrx_ptrs = NULL;
    if (rows < 0 || columns < 0)
        return NULL;

    mtrx = calloc(rows * columns, sizeof(double));
    if (!mtrx)
    {
        return NULL;
    }

    mtrx_ptrs = malloc(rows * sizeof (double*));
    if (!mtrx_ptrs)
    {
        free(mtrx);
        return NULL;
    }

    for (int i = 0; i < rows; i++)
    {
        mtrx_ptrs[i] = mtrx + i * columns;
        //printf("%f ", *(*(mtrx_ptrs + i)));
    }

    return mtrx_ptrs;
}

double** read_mtrx_from_file(char *file_name, double *mtrx, int *rows, int *columns)
{
    FILE *f = NULL;
    f = fopen(file_name, "r");

    double** mtrx_ptrs = NULL;
    if (f != NULL)
    {
        int i = 0, j = 0;
        int i_max = 0, j_max = 0;
        int input_rez = 0;

        input_rez = fscanf(f, "%d %d\n", &i_max, &j_max);
        if (input_rez != 2 || i_max > M || j_max > M)
            return NULL;

        //printf("read_mtrx_from_file - %p\n", mtrx_ptrs);
        mtrx_ptrs = matrix_malloc(mtrx, i_max, j_max);
        if (mtrx_ptrs == NULL)
            return NULL;
        //printf("read_mtrx_from_file - %p\n", mtrx_ptrs);

        double input = 0;

        while (feof(f) == 0)
        {
            while(j < j_max)
            {
                input_rez = fscanf(f, "%lf", &input);
                if (input_rez != 1)
                {
                    free(mtrx_ptrs);
                    free(mtrx);
                    return NULL;
                }
                //*((mtrx_ptrs[i]) + j) = input;
                *(*(mtrx_ptrs + i) + j) = input;
                //*((mtrx + i * (*rows)) + j) = input;
                j++;
            }
            i++;
            if (feof(f) != 0)
                break;
            j = 0;
        }

        if (i == i_max && j == j_max)
        {
            *columns = i;
            *rows = j;
        }
        else
        {
            free(mtrx_ptrs);
            free(mtrx);
            return NULL;
        }

    }
    else
        return NULL;
    fclose(f);

    return mtrx_ptrs;
}

void mtrx_addition(double **mtrx_ptrs1, double **mtrx_ptrs2, double **rez_mtrx_ptrs, int rows, int columns)
{
    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            *(*(rez_mtrx_ptrs + i) + j) = *(*(mtrx_ptrs1 + i) + j) + *(*(mtrx_ptrs2 + i) + j);
        }
    }
}

void print_mtrx(double **mtrx_ptrs, int rows, int columns)
{
    for (int i = 0; i < columns; i++)
    {
        for (int j = 0; j < rows; j++)
        {
            printf("%.3f ", *(*(mtrx_ptrs + i) + j));
        }
        printf("\n");
    }
    printf("\n");
}
