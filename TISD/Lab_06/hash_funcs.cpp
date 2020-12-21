#include "hash_funcs.h"
#include "tree_funcs.h"

int my_hash(string key, int m)
{
    int rez = 0;
    for (int i = 0; i < key.length(); i ++)
    {
        rez += key[i];
    }
    return rez % m;
}

hash_table_t *create_table(int m)
{
    hash_table_t *new_table = new hash_table_t;
    new_table->head = NULL;
    new_table->tail = NULL;
    new_table->max_size = m;
    return  new_table;
}

hash_table_line_t *create_line(string value, int m)
{
    hash_table_line_t *new_line = new hash_table_line_t;
    list_t *new_list = NULL;
    add_el_to_list(&new_list, value);
    new_line->cur_line = new_list;
    new_line->hash = my_hash(value, m);
    new_line->next_line = NULL;
    return new_line;
}

void add_line_to_table(hash_table_t *table, string value)
{
    hash_table_line_t *new_line = create_line(value, table->max_size);
    if (table->head == NULL)
    {
        table->head = new_line;
        table->tail = new_line;
    }
    else
    {
        table->tail->next_line = new_line;
        table->tail = new_line;
    }
}

void free_line(hash_table_line_t **line)
{
    list_t *tmp_list = (*line)->cur_line;
    free_list(&tmp_list);
    hash_table_line_t *ptr_to_delete = *line;
    *line = NULL;
    delete ptr_to_delete;
}

void free_table(hash_table_t **table)
{
    hash_table_line_t *tmp_line = (*table)->head;
    while (tmp_line != (*table)->tail)
    {
        hash_table_line_t *ptr_to_delete;
        tmp_line = tmp_line->next_line;
        free_line(&ptr_to_delete);
    }
    free_line(&tmp_line);
    (*table)->head = NULL;
    (*table)->tail = NULL;
    (*table)->max_size = -1;
    hash_table_t *ptr_to_delete = *table;
    *table = NULL;
    delete ptr_to_delete;
}

void get_table_from_tree(tree_node *root, list_t **table, int *size, int m)
{
    if (root)
    {
        get_table_from_tree(root->left, table, size, m);

        int cur_hash = my_hash(root->value, m);
        bool flag = true;
        for (int i = 0; i < *size; i++)
        {
            if (my_hash(table[i]->value, m) == cur_hash)
            {
                add_el_to_list(&table[i], root->value);
                flag = false;
            }
        }
        if (flag)
        {
            list_t *new_line = NULL;
            add_el_to_list(&new_line, root->value);
            size++;
        }

        get_table_from_tree(root->right, table, size, m);
    }
}

list_t *create_hash_table(tree_node *root)
{
    list_t *rez = NULL;
    int max_size = count_nodes(root);
    get_table_from_tree(root, &rez, 0, max_size);
    return rez;
}

/*void print_hash_table(list_t *arr)
{
    printf("\n------------------------------------------\n"
           "  ХЕШ | СООТВЕТСТВУЮЩИЕ ДАННЫЕ\n"
           "------------------------------------------\n");
    list_t *tmp = arr;

    int f = 0;

    for (int i = 0; i < size; i++)
    {
        f = 0;

        tmp = &arr[i];
        if (tmp != NULL)
        {
            printf("%5d | ", i);
            f = 1;
        }
        while (tmp != NULL)
        {
            if (tmp != NULL)
                printf("\"%s\" ", tmp->value.c_str());
            tmp = tmp->next;
        }
        if (f)
            printf("\n------------------------------------------\n");
    }
}*/
