#include "io_functions.h"

int read_args(int argc, char **argv, int *action, char *file_name1, char *file_name2, char *rez_file_name)
{
    switch (argc)
    {
        case 4:
        {
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
            *action = 0;
            break;
        }
        case 5:
        {
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
        }
        default:
            return CONSOLE_ARGS_ERROR;
            break;
    }
    return 0;
}

int output_rez(char *rez_file_name, double** mtrx_ptrs, int rows, int columns)
{
    FILE *f = NULL;
    f = fopen(rez_file_name, "w");

    fprintf(f, "%d %d\n", rows, columns);

    if (f != NULL)
    {
        for (int i = 0; i < columns; i++)
        {
            for (int j = 0; j < rows; j++)
            {
                fprintf(f, "%.3f ", *(*(mtrx_ptrs + i) + j));
            }
            fprintf(f, "\n");
        }
        fprintf(f, "\n");
    }
    else
        return FILE_OUTPUT_ERROR;

    fclose(f);

    return 0;
}
