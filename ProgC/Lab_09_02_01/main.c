#include "functions.h"
#include "io_funcs.h"

int main(int argc, char **argv)
{
    char file_name[M] = "";
    char prefix[M] = "";
    struct thing *list;
    int n = 0;

    if (read_args(argc, argv, prefix, file_name) != 0)
        return CONSOLE_ARGS_ERROR;

    list = read_file(file_name, &n);
    if (list == NULL)
        return FILE_READ_ERROR;

    output(prefix, list, n);

    return 0;
}
