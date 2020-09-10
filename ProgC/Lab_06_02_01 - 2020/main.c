#include "functions.h"

int main(int argc, char** argv)
{
    char file_name[M] = "";
    char prefix[M] = "";
    struct thing list[L];
	int n = 0;

	if (read_args(argc, argv, prefix, file_name) != 0)
		return CONSOLE_ARGS_ERROR;

	if (read_file(file_name, list, &n) !=0)
		return FILE_READ_ERROR;

	output(prefix, list, n);

	return 0;
}
