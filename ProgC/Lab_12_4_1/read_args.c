#include "defines.h"
#include "read_args.h"
#include <string.h>

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
