#include "defines.h"
#include "io_funcs.h"
#include "node_funcs.h"
#include <stdio.h>
#include <stdlib.h>

list_t *read_file(char *file_name)
{
    FILE *f = NULL;
    f = fopen(file_name, "r");

    list_t *list = NULL;

    if (f != NULL)
    {
        int i_max = 0;
        int j_max = 0;
        int input = 0;

        input = fscanf(f, "%d %d\n", &i_max, &j_max);

        if (input == 2 && i_max > 0 && j_max > 0)
        {
            list = create_list();
            for (int i = 0; i < i_max; i++)
            {
                for (int j = 0; j < j_max; j++)
                {
                    int tmp_int = 0;
                    input = fscanf(f, "%d", &tmp_int);
                    if (input != 1)
                    {
                        i = i_max;
                        j = j_max;
                    }
                    if (tmp_int != 0)
                    {
                        add(&list, i, j, tmp_int);
                    }
                }
            }
            if (input != 1)
            {
                free_list(&list);
            }
        }
        fclose(f);
    }

    return list;
}

list_t *read_mtrx()
{
    list_t *list = NULL;

    int i_max = 0;
    int j_max = 0;
    int input = 0;

    input = scanf("%d %d\n", &i_max, &j_max);

    if (input == 2 && i_max > 0 && j_max > 0)
    {
        list = create_list();
        for (int i = 0; i < i_max; i++)
        {
            for (int j = 0; j < j_max; j++)
            {
                int tmp_int = 0;
                input = scanf("%d", &tmp_int);
                if (input != 1)
                {
                    i = i_max;
                    j = j_max;
                }
                if (tmp_int != 0)
                {
                    add(&list, i, j, tmp_int);
                }
            }
        }
        if (input != 1)
        {
            free_list(&list);
        }
    }

    return list;
}

void print_node(node_t *head)
{
    if (head != NULL)
    {
        node_t *it = head;
        while (it != NULL)
        {
            printf("%d %d %d \n", it->data->row, it->data->column, it->data->value);
            it = it->next;
        }
    }
    else
    {
        printf("Mtrx is empty\n\n");
    }
    printf("\n");
}
