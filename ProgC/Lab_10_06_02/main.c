#include "defines.h"
#include "node_funcs.h"
#include "io_funcs.h"
#include <stdio.h>

int main()
{
    //list_t *test = read_mtrx();
    list_t *test1 = read_file("test3.txt");
    list_t *test2 = read_file("test4.txt");
    list_t *rez = compostion(test1, test2);

    print_node(rez->head);

    return 0;
}
