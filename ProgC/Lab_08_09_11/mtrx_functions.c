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

double **read_mtrx_from_file(char *file_name, double **mtrx, int *rows, int *columns)
{
    FILE *f = NULL;
    f = fopen(file_name, "r");

    double **mtrx_ptrs = NULL;
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

        while (fscanf(f, "%lf", &input) == 1)
        {
            //*(*(mtrx_ptrs + i) + j) = input;
            mtrx_ptrs[i][j] = input;
            j++;
            if (j == j_max)
            {
                j = 0;
                i++;
            }
        }

        /*while (feof(f) == 0)
        {
            while (j < j_max)
            {
                input_rez = fscanf(f, "%lf", &input);
                if (input_rez != 1)
                {
                    free(mtrx_ptrs);
                    free(mtrx);
                    return NULL;
                }
                // *((mtrx_ptrs[i]) + j) = input;
                *(*(mtrx_ptrs + i) + j) = input;
                //printf("%.3f ", *(*(mtrx_ptrs + i) + j));
                // *((mtrx + i * (*rows)) + j) = input;
                j++;
            }
            //printf("\n");
            i++;
            if (feof(f) != 0)
                break;
            j = 0;
        }*/
        //printf("\n");

        if (i == i_max && j == 0)
        {
            *rows = i_max;
            *columns = j_max;
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
    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            //*(*(rez_mtrx_ptrs + i) + j) = *(*(mtrx_ptrs1 + i) + j) + *(*(mtrx_ptrs2 + i) + j);
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
            *(*(rez_mtrx_ptrs + i) + j) = 0;
            for (int k = 0; k < columns1; k++)
            {
                //*(*(rez_mtrx_ptrs + i) + j) += *(*(mtrx_ptrs1 + i) + k) * *(*(mtrx_ptrs2 + k) + j);
                rez_mtrx_ptrs[i][j] += mtrx_ptrs1[i][k] * mtrx_ptrs2[k][j];
            }
        }
    }
}

double **solve_mtrx(double **mtrx_ptrs_start, int rows, int columns, double *x_mtrx)
{
    int r = rows, c = columns;
    double **rez_mtrx_ptrs = NULL;
    double *rez_mtrx = NULL;
    rez_mtrx_ptrs = matrix_malloc(&rez_mtrx, rows, columns);
    if (!rez_mtrx_ptrs)
    {
        return NULL;
    }

    double **mtrx_ptrs = NULL;
    double *mtrx = NULL;
    mtrx_ptrs = matrix_malloc(&mtrx, rows, columns);
    if (!mtrx_ptrs)
    {
        free(rez_mtrx_ptrs);
        free(rez_mtrx);
        return NULL;
    }

    for (int i = 0; i < rows; i++)
    {
        for (int j = 0; j < columns; j++)
        {
            //*(*(mtrx_ptrs + i) + j) = *(*(mtrx_ptrs_start + i) + j);
            mtrx_ptrs[i][j] = mtrx_ptrs_start[i][j];
        }
    }
    //print_mtrx(mtrx_ptrs, rows, columns);

    for (int k = 0; k < rows; k++)
    {
        //double am = *(*(mtrx_ptrs));
        double am = mtrx_ptrs[0][0];
        int m = 0;
        for (int i = 0; i < r; i++)
        {
            /*if (am < *(*(mtrx_ptrs + i)))
            {
                am = *(*(mtrx_ptrs + i));
                m = i;
            }*/
            if ((am < mtrx_ptrs[i][0] || am == 0) && mtrx_ptrs[i][0] != 0)
            {
                am = mtrx_ptrs[i][0];
                m = i;
            }
        }
        //printf("%f\n\n", am);

        if (am == 0)
        {
            free(rez_mtrx_ptrs);
            free(rez_mtrx);
            free(mtrx_ptrs);
            free(mtrx);
            return NULL;
        }

        for (int j = 0; j < c; j++)
        {
            //printf("%.3f ", *(*(mtrx_ptrs + m) + j));
            //*(*(rez_mtrx_ptrs + k) + j + k) = *(*(mtrx_ptrs + m) + j);
            rez_mtrx_ptrs[k][j + k] = mtrx_ptrs[m][j];
        }
        //printf("\n");

        double **tmp_mtrx_ptrs = NULL;
        double *tmp_mtrx = NULL;
        tmp_mtrx_ptrs = matrix_malloc(&tmp_mtrx, r - 1, c - 1);
        if (!tmp_mtrx_ptrs)
        {
            free(rez_mtrx_ptrs);
            free(rez_mtrx);
            free(mtrx_ptrs);
            free(mtrx);
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
                    //*(*(tmp_mtrx_ptrs + l) + j) = *(*(mtrx_ptrs + i) + j + 1) + *(*(mtrx_ptrs + m) + j + 1) * mi;
                    tmp_mtrx_ptrs[l][j] = mtrx_ptrs[i][j + 1] + mtrx_ptrs[m][j + 1] * mi;
                    //printf(" = %.3f\n", *(*(tmp_mtrx_ptrs + l) + j));
                    //if (*(*(tmp_mtrx_ptrs + l) + j) == 0)
                    /*if (tmp_mtrx_ptrs[l][j] == 0)
                        return NULL;*/
                }
                l++;
            }
        }
        /*printf("tmp_mtrx_ptrs:\n");
        print_mtrx(tmp_mtrx_ptrs, r - 1, c - 1);
        printf("rez_mtrx_ptrs:\n");
        print_mtrx(rez_mtrx_ptrs, rows, columns);*/
        c--; r--;

        free(mtrx_ptrs);
        free(mtrx);

        if (k != rows - 1)
        {
            mtrx_ptrs = matrix_malloc(&mtrx, r, c);

            for (int i = 0; i < r; i++)
            {
                for (int j = 0; j < c; j++)
                {
                    //*(*(mtrx_ptrs + i) + j) = *(*(tmp_mtrx_ptrs + i) + j);
                    mtrx_ptrs[i][j] = tmp_mtrx_ptrs[i][j];
                }
            }
            //printf("mtrx_ptrs:\n");
            //print_mtrx(mtrx_ptrs, r, c);
        }

        free(tmp_mtrx_ptrs);
        free(tmp_mtrx);
    }

    //printf("REZ_END\n\n");

    double **x_mtrx_ptrs = NULL;
    //double *x_mtrx = NULL;
    x_mtrx = NULL;
    x_mtrx_ptrs = matrix_malloc(&x_mtrx, rows, 1);
    if (!x_mtrx_ptrs)
    {
        free(rez_mtrx_ptrs);
        free(rez_mtrx);
        return NULL;
    }

    for (int i = rows - 1; i >= 0; i--)
    {
        //double tmp = *(*(rez_mtrx_ptrs + i) + columns - 1);
        double tmp = rez_mtrx_ptrs[i][columns - 1];
        for (int j = columns - 2; j > i; j--)
        {
            //tmp -= *(*(rez_mtrx_ptrs + i) + j);
            tmp -= rez_mtrx_ptrs[i][j];
        }
        //printf("%f = ", tmp / *(*(rez_mtrx_ptrs + i) + i));
        //*(*(x_mtrx_ptrs + i)) = tmp / *(*(rez_mtrx_ptrs + i) + i);
        x_mtrx_ptrs[i][0] = tmp / rez_mtrx_ptrs[i][i];
        //printf("%f\n", *(*(x_mtrx_ptrs + i)));
        for (int j = 0; j < i; j++)
        {
            //printf("%f * %f = ", *(*(rez_mtrx_ptrs + j) + i), *(*(x_mtrx_ptrs + i)));
            //*(*(rez_mtrx_ptrs + j) + i) *= *(*(x_mtrx_ptrs + i));
            rez_mtrx_ptrs[j][i] *= x_mtrx_ptrs[i][0];
            //printf("%f\n", *(*(rez_mtrx_ptrs + j) + i));
        }
        //print_mtrx(rez_mtrx_ptrs, rows, columns);
    }

    free(rez_mtrx_ptrs);
    free(rez_mtrx);

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
