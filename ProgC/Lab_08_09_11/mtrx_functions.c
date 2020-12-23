#include "mtrx_functions.h"

double **matrix_malloc(double **mtrx_rez, int rows, int columns)
{
    if (rows < 0 || columns < 0)
        return NULL;

    double **mtrx_ptrs = NULL;

    double *mtrx = NULL;
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

    //printf("%p %p\n", *mtrx_rez, mtrx);
    *mtrx_rez = mtrx;
    //printf("%p %p\n", *mtrx_rez, mtrx);
    return mtrx_ptrs;
}

double **matrix_malloc2(int rows, int columns)
{
    if (rows <= 0 || columns <= 0)
        return NULL;

    double **mtrx_ptrs = NULL;

    double *mtrx = NULL;
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

    //printf("%p %p\n", *mtrx_rez, mtrx);
    //*mtrx_rez = mtrx;
    //printf("%p %p\n", *mtrx_rez, mtrx);
    return mtrx_ptrs;
}

void free_mtrx(double **mtrx_ptrs)
{
    free(mtrx_ptrs[0]);
    free(mtrx_ptrs);
}

void mtrx_addition(double **mtrx_ptrs1, double **mtrx_ptrs2, double **rez_mtrx_ptrs, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            rez_mtrx_ptrs[i][j] = mtrx_ptrs1[i][j] + mtrx_ptrs2[i][j];
        }
    }
}

void mtrx_composition(double **mtrx_ptrs1, double **mtrx_ptrs2, double **rez_mtrx_ptrs, int rows, int columns, int columns1)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            //*(*(rez_mtrx_ptrs + i) + j) = 0;
            for (int k = 0; k < columns1; k++)
            {
                rez_mtrx_ptrs[i][j] += mtrx_ptrs1[i][k] * mtrx_ptrs2[k][j];
            }
        }
    }
}

double **solve_mtrx(double **mtrx_ptrs_start, int rows, int columns)
{
    int r = rows, c = columns;
    double **rez_mtrx_ptrs = NULL;
    rez_mtrx_ptrs = matrix_malloc2(rows, columns);
    if (rez_mtrx_ptrs == NULL)
    {
        return NULL;
    }

    double **mtrx_ptrs = NULL;
    mtrx_ptrs = matrix_malloc2(rows, columns);
    if (mtrx_ptrs == NULL)
    {
        free_mtrx(rez_mtrx_ptrs);
        return NULL;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            mtrx_ptrs[i][j] = mtrx_ptrs_start[i][j];
        }
    }
    //print_mtrx(mtrx_ptrs, rows, columns);

    for (int k = 0; k < rows; k++)
    {
        double am = mtrx_ptrs[0][0];
        int m = 0;
        for (int i = 0; i < r; i++)
        {
            if ((am < mtrx_ptrs[i][0] || am == 0) && mtrx_ptrs[i][0] != 0)
            {
                am = mtrx_ptrs[i][0];
                m = i;
            }
        }
        //printf("%f\n\n", am);

        if (am == 0)
        {
            free_mtrx(mtrx_ptrs);
            free_mtrx(rez_mtrx_ptrs);
            return NULL;
        }

        for (int j = 0; j < c; j++)
        {
            //printf("%.3f ", *(*(mtrx_ptrs + m) + j));
            rez_mtrx_ptrs[k][j + k] = mtrx_ptrs[m][j];
        }
        //printf("\n");

        double **tmp_mtrx_ptrs = NULL;

        if (k != rows - 1)
        {
            tmp_mtrx_ptrs = matrix_malloc2(r - 1, c - 1);
            if (tmp_mtrx_ptrs == NULL)
            {
                free_mtrx(mtrx_ptrs);
                free_mtrx(rez_mtrx_ptrs);
                return NULL;
            }

            int l = 0;
            for (int i = 0; i < r; i++)
            {
                if (i != m)
                {
                    double mi = - *(*(mtrx_ptrs + i)) / am;
                    for (int j = 0; j < c - 1; j++)
                    {
                        //printf("(%.3f) + (%.3f)", *(*(mtrx_ptrs + i) + j + 1), *(*(mtrx_ptrs + m) + j + 1) * mi);
                        tmp_mtrx_ptrs[l][j] = mtrx_ptrs[i][j + 1] + mtrx_ptrs[m][j + 1] * mi;
                        //printf(" = %.3f\n", *(*(tmp_mtrx_ptrs + l) + j));
                    }
                    l++;
                }
            }
        }
        /*printf("tmp_mtrx_ptrs:\n");
        print_mtrx(tmp_mtrx_ptrs, r - 1, c - 1);
        printf("rez_mtrx_ptrs:\n");
        print_mtrx(rez_mtrx_ptrs, rows, columns);*/
        c--; r--;

        free_mtrx(mtrx_ptrs);

        if (k != rows - 1)
        {
            mtrx_ptrs = matrix_malloc2(r, c);

            for (int i = 0; i < r; i++)
            {
                for (int j = 0; j < c; j++)
                {
                    mtrx_ptrs[i][j] = tmp_mtrx_ptrs[i][j];
                }
            }
            //printf("mtrx_ptrs:\n");
            //print_mtrx(mtrx_ptrs, r, c);

            //print_mtrx(tmp_mtrx_ptrs, r, c);
            free_mtrx(tmp_mtrx_ptrs);
        }  
    }

    //printf("REZ_END\n\n");

    double **x_mtrx_ptrs = NULL;
    x_mtrx_ptrs = matrix_malloc2(rows, 1);
    if (x_mtrx_ptrs == NULL)
    {
        free_mtrx(rez_mtrx_ptrs);
        return NULL;
    }

    for (int i = rows - 1; i >= 0; i--)
    {
        double tmp = rez_mtrx_ptrs[i][columns - 1];
        for (int j = columns - 2; j > i; j--)
        {
            tmp -= rez_mtrx_ptrs[i][j];
        }
        //printf("%f = ", tmp / *(*(rez_mtrx_ptrs + i) + i));
        x_mtrx_ptrs[i][0] = tmp / rez_mtrx_ptrs[i][i];
        //printf("%f\n", *(*(x_mtrx_ptrs + i)));
        for (int j = 0; j < i; j++)
        {
            //printf("%f * %f = ", *(*(rez_mtrx_ptrs + j) + i), *(*(x_mtrx_ptrs + i)));
            rez_mtrx_ptrs[j][i] *= x_mtrx_ptrs[i][0];
            //printf("%f\n", *(*(rez_mtrx_ptrs + j) + i));
        }
        //print_mtrx(rez_mtrx_ptrs, rows, columns);
    }

    free_mtrx(rez_mtrx_ptrs);

    //print_mtrx(x_mtrx_ptrs, rows, 1);
    return x_mtrx_ptrs;
}

void print_mtrx(double **mtrx_ptrs, int rows, int columns)
{
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            printf("%.3f ", *(*(mtrx_ptrs + i) + j));
        }
        printf("\n");
    }
    printf("\n");
}
