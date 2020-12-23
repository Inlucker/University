#include "io_functions.h"
#include "mtrx_functions.h"

int read_args(int argc, char **argv, int *action, char *file_name1, char *file_name2, char *rez_file_name)
{
    switch (argc)
    {
        case 4:
            if (strcmp(argv[1], "o") == 0)
            {
                *action = 3;
            }
            else if (strcmp(argv[1], "a") == 0)
            {
                *action = 1;
                return CONSOLE_ARGS_ERROR;
            }
            else if (strcmp(argv[1], "m") == 0)
            {
                *action = 2;
                return CONSOLE_ARGS_ERROR;
            }
            else
                return CONSOLE_ARGS_ERROR;

            if (strlen(argv[2]) > M || strlen(argv[3]) > M)
                return CONSOLE_ARGS_ERROR;

            strcpy(file_name1, argv[2]);
            strcpy(rez_file_name, argv[3]);
            break;
        case 5:
            if (strcmp(argv[1], "a") == 0)
            {
                *action = 1;
            }
            else if (strcmp(argv[1], "m") == 0)
            {
                *action = 2;
            }
            else if (strcmp(argv[1], "o") == 0)
            {
                *action = 3;
                return CONSOLE_ARGS_ERROR;
            }
            else
                return CONSOLE_ARGS_ERROR;

            if (strlen(argv[2]) > M || strlen(argv[3]) > M || strlen(argv[4]) > M)
                return CONSOLE_ARGS_ERROR;

            strcpy(file_name1, argv[2]);
            strcpy(file_name2, argv[3]);
            strcpy(rez_file_name, argv[4]);
            break;
        default:
            return CONSOLE_ARGS_ERROR;
            break;
    }
    return 0;
}

double **read_mtrx_from_file(char *file_name, int *r, int *c)
{
    FILE *f = NULL;
    f = fopen(file_name, "r");

    double **mtrx_ptrs = NULL;

    if (f != NULL)
    {
        int i_max = 0, j_max = 0;
        fscanf(f, "%d %d", &i_max, &j_max);

        if (i_max > 0 && j_max > 0)
        {
            *r = i_max;
            *c = j_max;

            mtrx_ptrs = matrix_malloc2(i_max, j_max);

            if (mtrx_ptrs != NULL)
                for (int i = 0; i < i_max; i++)
                    for (int j = 0; j < j_max; j++)
                        if (fscanf(f, "%lf", &mtrx_ptrs[i][j]) != 1)
                        {
                            free_mtrx(mtrx_ptrs);
                            mtrx_ptrs = NULL;
                            i = i_max;
                            break;
                        }
            fscanf(f, "\n");
            //printf("%d\n", feof(f));
            if (!feof(f))
            {
                free_mtrx(mtrx_ptrs);
                mtrx_ptrs = NULL;
            }
        }
        fclose(f);
    }

    return mtrx_ptrs;
}

int output_rez(char *rez_file_name, double **mtrx_ptrs, int rows, int columns)
{
    FILE *f = NULL;

    f = fopen(rez_file_name, "w");

    if (f != NULL)
    {
        fprintf(f, "%d %d\n", rows, columns);
        for (int i = 0; i < rows; i++)
        {
            for (int j = 0; j < columns; j++)
            {
                //fprintf(f, "%f ", *(*(mtrx_ptrs + i) + j));
                fprintf(f, "%f ", mtrx_ptrs[i][j]);
            }
            fprintf(f, "\n");
        }
        //fprintf(f, "\n");
    }
    else
        return FILE_OUTPUT_ERROR;

    fclose(f);

    return 0;
}

int output_solvation(char *rez_file_name, double **mtrx_ptrs, int rows)
{
    FILE *f = NULL;
    f = fopen(rez_file_name, "w");

    if (f != NULL)
    {
        for (int j = 0; j < rows; j++)
        {
            fprintf(f, "%f ", *(*(mtrx_ptrs + j)));
        }
    }
    else
        return FILE_OUTPUT_ERROR;

    fclose(f);

    return 0;
}
