#include "defines.h"
#include "io_funcs.h"
#include "node_funcs.h"
#include "comporators.h"
#include <stdio.h>

int main()
{
    printf("Hello World!\n");

    node_t *test = read_file("test.txt");
    node_t *test2 = read_file("test.txt");
    //print_infos(test);

    sort(&test, (int(*)(const void *, const void *)) comp_info);

    //print_infos(test);

    pop_back(&test);

    //print_infos(test);

    pop_front(&test);

    print_infos(test);
    print_infos(test2);

    append(&test2, &test);

    print_infos(test);
    print_infos(test2);

    free_list(&test2);
    //free_list(&test2);

    print_infos(test);
    print_infos(test2);
    return 0;
}
