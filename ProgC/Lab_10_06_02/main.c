#include "defines.h"
#include "node_funcs.h"
#include "io_funcs.h"
#include <stdio.h>
#include <string.h>

int main()
{
    char input[N];

    if (scanf("%s", input) != 1)
        return ARGS_ERROR;
    if (!strcmp(input, "out"))
    {
        list_t *list = read_mtrx();
        if (!list)
            return INPUT_ERROR;

        print_list(list);

        free_list(&list);
    }
    else if (!strcmp(input, "add"))
    {
        list_t *list1 = read_mtrx();
        if (!list1)
            return INPUT_ERROR;
        list_t *list2 = read_mtrx();
        if (!list2)
            return INPUT_ERROR;
        list_t *rez = addition(list1, list2);

        print_list(rez);

        free_list(&list1);
        free_list(&list2);
        free_list(&rez);
    }
    else if (!strcmp(input, "mul"))
    {
        list_t *list1 = read_mtrx();
        if (!list1)
            return INPUT_ERROR;
        list_t *list2 = read_mtrx();
        if (!list2)
            return INPUT_ERROR;
        list_t *rez = compostion(list1, list2);

        print_list(rez);

        free_list(&list1);
        free_list(&list2);
        free_list(&rez);
    }
    else if (!strcmp(input, "lin"))
    {
        list_t *list = read_mtrx();
        if (!list)
            return INPUT_ERROR;
        delete_max_line(list);

        print_list(list);

        free_list(&list);
    }
    else
        return ARGS_ERROR;

    return 0;
}
