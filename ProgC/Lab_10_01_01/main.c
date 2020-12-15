#include "defines.h"
#include "io_funcs.h"
#include "node_funcs.h"
#include "comporators.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Hello World!\n");

    node_t *test = read_file("test2.txt");
    //node_t *test2 = read_file("test2.txt");
    print_infos(test);

    test = sort(test, (int(*)(const void *, const void *)) comp_info);

    //print_infos(test);

    /*info_t *back = pop_back(&test);
    free(back);

    print_infos(test);

    info_t *front = pop_front(&test);
    free(front);

    print_infos(test);
    print_infos(test2);

    append(&test2, &test);

    print_infos(test);
    print_infos(test2);*/

    print_infos(test);

    free_list(&test);
    //free_list(&test2);

    print_infos(test);
    //print_infos(test2);
    return 0;
}
