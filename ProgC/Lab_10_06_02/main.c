#include "defines.h"
#include "node_funcs.h"
#include "io_funcs.h"
#include <stdio.h>

int main()
{
    list_t *test = read_file("test.txt");

    print_node(test->head);

    return 0;
}
