#include "io_funcs.h"
#include "node_funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

node_t *read_file(char *file_name)
{
    FILE *f = NULL;
    f = fopen(file_name, "r");

    node_t *list = NULL;

    if (f != NULL)
    {
        int i = 0, i_max = 0;
        int input = 0;

        while (!feof(f))
        {
            //fscanf(f, "%*[^\n]%*c");
            char tmp_name[N] = "";
            input = fscanf(f, "%s\n", tmp_name);
            //printf("%d\n", strlen(tmp_name));
            if (input != 1 || strlen(tmp_name) > N)
            {
                i_max = 0;
                break;
            }

            int tmp_int = 0;
            input = fscanf(f, "%d\n", &tmp_int);
            if (input != 1)
            {
                i_max = 0;
                break;
            }

            double tmp_double = 0.0;
            input = fscanf(f, "%lf\n", &tmp_double);
            if (input != 1)
            {
                i_max = 0;
                break;
            }

            i_max++;
        }

        if (i_max > 0)
        {
            fseek(f, 0L, SEEK_SET);

            while (feof(f) == 0)
            {
                if (i >= i_max)
                {
                    input = -1;
                    break;
                }

                info_t *tmp_data = malloc(sizeof(info_t));

                input = fscanf(f, "%s\n", tmp_data->name);
                if (input != 1)
                    break;

                input = fscanf(f, "%d\n", &tmp_data->years);

                input = fscanf(f, "%lf\n", &tmp_data->intelect);
                //here
                add(&list, tmp_data);

                i++;
            }
            if (i != i_max || input != 1)
            {
                free_list(&list);
                list = NULL;
            }
        }
        fclose(f);
    }

    return list;
}

void print_infos(node_t *head)
{
    if (head != NULL)
    {
        node_t *tmp = head;
        do
        {
            info_t *tmp_data = tmp->data;
            printf("Data: %s %d %lf\n", tmp_data->name, tmp_data->years, tmp_data->intelect);
            //printf("Next_ptr: %p\n", tmp->next);
            tmp = tmp->next;
        } while (tmp != NULL);
        printf("\n");
    }
    else
    {
        printf("List is empty\n\n");
    }
}
