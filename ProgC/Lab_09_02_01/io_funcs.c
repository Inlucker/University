#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "io_funcs.h"
#include "functions.h"

int read_args(int argc, char **argv, char *prefix, char *file_name)
{
    switch (argc)
    {
        case 2:
            if (strlen(argv[1]) > M)
            {
                //printf("Too long file name\n");
                return CONSOLE_ARGS_ERROR;
            }
            strcpy(file_name, argv[1]);
            break;
        case 3:
            if (strlen(argv[1]) > M || strlen(argv[2]) > M)
            {
                //printf("Too long file or prefix name\n");
                return CONSOLE_ARGS_ERROR;
            }
            strcpy(prefix, argv[2]);
            strcpy(file_name, argv[1]);
            break;
        default:
            //printf("Console args error\n");
            return CONSOLE_ARGS_ERROR;
            break;
    }
    return 0;
}

struct thing *read_file(char *file_name, int *n)
{
    FILE *f = NULL;
    f = fopen(file_name, "r");

    struct thing *list = NULL;

    if (f != NULL)
    {
        int i = 0, i_max = 0;;
        int input = 0;

        while (!feof(f))
        {
            if (fgetc(f) == '\n')
                i_max++;
        }

        if (i_max % 3 == 0)
            i_max /= 3;
        else
            return NULL;

        if (i_max > L)
        {
            //printf("Too much information in File\n");
            return NULL;
        }

        *n = i_max;

        list = malloc(sizeof(struct thing) * i_max);

        fseek(f, 0L, SEEK_SET);

        while (feof(f) == 0)
        {
            input = fscanf(f, "%s\n", list[i].name);

            if (input != 1 || strlen(list[i].name) > N)
                return NULL;

            input = fscanf(f, "%f\n", &list[i].m);

            if (input != 1 || list[i].m <= 0 || list[i].m - 1.7976931348623157e+308 > 0)
                return NULL;

            input = fscanf(f, "%f\n", &list[i].v);
            if (input != 1 || list[i].v <= 0 || list[i].v - 1.7976931348623157e+308 > 0)
                return NULL;

            list[i].p = list[i].m / list[i].v;
            //printf("p%d = %f\n", i, list[i].p);
            i++;
        }
    }
    else
    {
        //printf("File read error\n");
        return NULL;
    }
    fclose(f);

    return list;
}

void print_things(struct thing *mas, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%s: ", mas[i].name);
        printf("m%d = %f; ", i, mas[i].m);
        printf("v%d = %f; ", i, mas[i].v);
        printf("p%d = %f\n", i, mas[i].p);
    }
    printf("\n");
}

void output(char *prefix, struct thing *list, int n)
{
    if (strcmp(prefix, "") == 0)
    {
        quick_sort(list, 0, n - 1);
        for (int i = 0; i < n; i++)
            print(&list[i]);
    }
    else if (strcmp(prefix, "ALL") == 0)
        for (int i = 0; i < n; i++)
            print(&list[i]);
    else
        for (int i = 0; i < n; i++)
            if (strncmp(prefix, list[i].name, strlen(prefix)) == 0)
                print(&list[i]);
}

void print(struct thing *list)
{
    printf("%s\n%.6f\n%.6f\n", list->name, list->m, list->v);
}
