#include "io_funcs.h"

int read_file_n(char *file_name, int *n)
{
    FILE *f = NULL;
    f = fopen(file_name, "r");

    if (f != NULL)
    {
        int i = 0;
        int input_rez = 0;

        int input = 0;

        while (feof(f) == 0)
        {
            input_rez = fscanf(f, "%d\n", &input);

            if (input_rez != 1)
                return FILE_READ_ERROR;
            i++;
        }
        *n = i;
    }
    else
        return FILE_READ_ERROR;
    fclose(f);

    return 0;
}

int read_file(char *file_name, int *mas)
{
    FILE *f = NULL;
    f = fopen(file_name, "r");

    if (f != NULL)
    {
        int i = 0;
        int input_rez = 0;

        int input = 0;

        while (feof(f) == 0)
        {
            input_rez = fscanf(f, "%d\n", &input);

            if (input_rez != 1)
                return FILE_READ_ERROR;

            //printf("%d", mas[i]);
            mas[i] = input;

            i++;
        }
    }
    else
        return FILE_READ_ERROR;
    fclose(f);

    return 0;
}

int read_args(int argc, char **argv, int *filtr, char *input_file_name, char *output_file_name)
{
    switch (argc)
    {
        case 3:
            if (strlen(argv[1]) > M || strlen(argv[2]) > M)
                return CONSOLE_ARGS_ERROR;
            strcpy(input_file_name, argv[1]);
            strcpy(output_file_name, argv[2]);
            *filtr = 0;
            break;
        case 4:
            if (strlen(argv[1]) > M || strlen(argv[2]) > M)
                return CONSOLE_ARGS_ERROR;
            strcpy(input_file_name, argv[1]);
            strcpy(output_file_name, argv[2]);
            if (strcmp(argv[3], "f") == 0)
                *filtr = 1;
            else
                return CONSOLE_ARGS_ERROR;
            break;
        default:
            return CONSOLE_ARGS_ERROR;
            break;
    }
    return 0;
}

int output(char *file_name, int *mas, int n)
{
    FILE *f = NULL;
    f = fopen(file_name, "w");

    if (f != NULL)
        for (int i = 0; i < n; i++)
            fprintf(f, "%d ", mas[i]);
    else
        return FILE_OUTPUT_ERROR;

    fclose(f);
    return 0;
}
