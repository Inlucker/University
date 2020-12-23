#include "defines.h"
#include "io_funcs.h"
#include "node_funcs.h"
#include "comporators.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    printf("Testing sort, pop_back, pop_front and append functions:\n");

    node_t *test = read_file("test2.txt");
    printf("First list (before sort):\n");
    print_infos(test);

    test = sort(test, (int(*)(const void *, const void *)) comp_info);

    printf("First list (after sort):\n");
    print_infos(test);

    info_t *back = pop_back(&test);
    printf("Pop_back info:\n%s %d %f\n\n", back->name, back->years, back->intelect);
    free(back);

    printf("First list:\n");
    print_infos(test);

    info_t *front = pop_front(&test);
    printf("Pop_front info:\n%s %d %f\n\n", front->name, front->years, front->intelect);
    free(front);

    node_t *test2 = read_file("test.txt");

    printf("Second list (before sort):\n");
    print_infos(test2);

    test2 = sort(test2, (int(*)(const void *, const void *)) comp_info);

    printf("Second list (after sort):\n");
    print_infos(test2);

    printf("Before append (First to Second):\n");
    printf("First list:\n");
    print_infos(test);
    printf("Second list:\n");
    print_infos(test2);

    append(&test2, &test);

    printf("After append (First to Second):\n");
    printf("First list:\n");
    print_infos(test);
    printf("Second list:\n");
    print_infos(test2);

    free_list(&test);
    free_list(&test2);

    printf("Check lists after free:\n");
    printf("First list:\n");
    print_infos(test);
    printf("Second list:\n");
    print_infos(test2);
    return 0;
}
