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
    new_table->mas_size = m;
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
    hash_table_line_t *new_line = create_line(value, table->mas_size);
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
    (*table)->mas_size = -1;
    hash_table_t *ptr_to_delete = *table;
    *table = NULL;
    delete ptr_to_delete;
}

void get_table_from_tree(tree_node *root, hash_table_t *table, int *size, int m)
{
    if (root)
    {
        get_table_from_tree(root->left, table, size, m);

        int cur_hash = my_hash(root->value, m);
        bool flag = true;
        hash_table_line_t *tmp_line = table->head;
        while (tmp_line)
        {
            if (tmp_line->hash == cur_hash)
            {
                flag = false;
                break;
            }
            tmp_line = tmp_line->next_line;
        }

        if (flag)
            add_line_to_table(table, root->value);
        else
            add_el_to_list(&tmp_line->cur_line, root->value);

        get_table_from_tree(root->right, table, size, m);
    }
}

hash_table_t *create_hash_table(tree_node *root)
{
    int mas_size = count_nodes(root);
    bool is_simple = false;

    while (!is_simple)
    {
        mas_size++;
        is_simple = true;
        for (int i = 2; i < mas_size/2; i++)
        {
            if (mas_size % i == 0)
            {
                is_simple = false;
                break;
            }
        }

    }

    hash_table_t *rez = create_table(mas_size);
    get_table_from_tree(root, rez, 0, mas_size);
    return rez;
}

void print_hash_table(hash_table_t *table)
{
    hash_table_line_t *tmp_line = table->head;
    while (tmp_line)
    {
        list_t *tmp_list = tmp_line->cur_line;
        cout << tmp_line->hash << ": ";
        while (tmp_list)
        {
            cout << " " << tmp_list->value;
            tmp_list = tmp_list->next;
        }
        cout << endl;
        tmp_line = tmp_line->next_line;
    }
}
