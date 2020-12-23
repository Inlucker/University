#include "defines.h"
#include "read_args.h"
#include <stdio.h>

int main(int argc, char **argv)
{
    char input_file_name[M] = "";
    char output_file_name[M] = "";
    int filtr_flag = 0;
    int n = 0;
    int *mas = NULL;

    if (read_args(argc, argv, &filtr_flag, input_file_name, output_file_name) != 0)
        return CONSOLE_ARGS_ERROR;

    return 0;
}
