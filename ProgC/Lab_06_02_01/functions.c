/*!
  \file
  \brief Исходный файл содержащий в себе реализации всех используемых функций
  */
#include "functions.h"

void quick_sort(struct thing *a, int l, int r)
{
    int i = l, j = r;
    float m = a[(l + r) / 2].p;
    do
    {
        for (; a[i].p < m; i++);
        for (; a[j].p > m; j--);
        if (i <= j)
        {
            struct thing tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
            i++;
            j--;
        }
    }while (i <= j);
    if (l < j)
        quick_sort(a, l, j);
    if (i < r)
        quick_sort(a, i, r);
}

int read_args(int argc, char **argv, char *prefix, char *file_name)
{
    switch (argc)
    {
        case 2:
            strcpy(file_name, argv[1]);
            break;
        case 3:
            strcpy(prefix, argv[2]);
            if (strlen(argv[1]) > M)
            {
                //printf("Too long file name\n");
                return CONSOLE_ARGS_ERROR;
            }
            strcpy(file_name, argv[1]);
            break;
        default:
            //printf("Console args error\n");
            return CONSOLE_ARGS_ERROR;
            break;
    }
    return 0;
}

int read_file(char *file_name, struct thing list[], int *n)
{
	FILE *f = NULL;
    f = fopen(file_name, "r");

    if (f != NULL)
    {
        int i = 0;
        int input = 0;

        while (feof(f) == 0)
        {
            input = fscanf(f, "%s\n", list[i].name);

            if (input == -1)
                return FILE_READ_ERROR;

            if (input != 1 || strlen(list[i].name) > N)
                return FILE_READ_ERROR;

            input = fscanf(f, "%f\n", &list[i].m);

            if (input != 1 || list[i].m <= 0 || list[i].m - 1.7976931348623157e+308 > 0)
                return FILE_READ_ERROR;

            input = fscanf(f, "%f\n", &list[i].v);
            if (input != 1 || list[i].v <= 0 || list[i].v - 1.7976931348623157e+308 > 0)
                return FILE_READ_ERROR;

            list[i].p = list[i].m / list[i].v;
            i++;
        }
        if (i > L)
        {
            //printf("Too much information in File\n");
            return FILE_READ_ERROR;
        }
        *n = i;
    }
    else
    {
        //printf("File read error\n");
        return FILE_READ_ERROR;
    }
    fclose(f);

    return 0;
}

void output(char *prefix, struct thing list[], int n)
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
