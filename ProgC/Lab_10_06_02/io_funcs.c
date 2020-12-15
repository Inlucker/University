#include "defines.h"
#include "io_funcs.h"
#include "node_funcs.h"
#include <stdio.h>
#include <stdlib.h>

node_t *read_file(char *file_name)
{
    FILE *f = NULL;
    f = fopen(file_name, "r");

    node_t *list = NULL;

    if (f != NULL)
    {
        int i_max = 0;
        int j_max = 0;
        int input = 0;

        input = fscanf(f, "%d %d\n", &i_max, &j_max);

        if (input == 2 && i_max > 0 && j_max > 0)
        {
            /*int i = 0;
            int j = 0;
            while (!feof(f))
            {

            }*/
            //WORKING HERE
            for (int i = 0; i < i_max; i++)
            {
                for (int j = 0; j < j_max; j++)
                {
                    int tmp_int = 0;
                    input = fscanf(f, "%d", &tmp_int);
                    if (tmp_int != 0)
                    {
                        elem_t *tmp_elem = malloc(sizeof (elem_t));
                        tmp_elem->row = i;
                        tmp_elem->column = j;
                    }
                    if (input != 1)
                    {

                    }
                }
            }
        }
        fclose(f);
    }

    return list;
}

void print_mtrx(node_t *head)
{
    if (head != NULL)
    {

    }
    else
    {
        printf("Mtrx is empty\n\n");
    }
}
