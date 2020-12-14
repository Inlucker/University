#include "defines.h"
#include "io_funcs.h"
#include "node_funcs.h"
#include "comporators.h"
#include <stdio.h>

int main()
{
    printf("Hello World!\n");

    node_t *test = read_file("test.txt");
    print_infos(test);

    sort(&test, (int(*)(const void *, const void *)) comp_info);

    print_infos(test);
    free_list(&test);
    return 0;
}
