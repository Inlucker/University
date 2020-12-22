#ifndef STRUCTURES_H
#define STRUCTURES_H
#include "defines.h"

struct list_t
{
    string value;
    list_t *next;
};

//NOT USING
/*struct hash_table_line_t
{
    list_t *cur_line;
    int hash;
    hash_table_line_t *next_line;
};

//NOT USING
struct hash_table_t
{
    hash_table_line_t *head;
    hash_table_line_t *tail;
    int mas_size;
};*/

struct tree_node
{
    string value;
    tree_node *left;
    tree_node *right;
};

#endif // STRUCTURES_H
