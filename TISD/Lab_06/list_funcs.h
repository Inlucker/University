#ifndef LIST_FUNCS_H
#define LIST_FUNCS_H

#include "defines.h"
#include "structures.h"

//list_t *create_list(string value);

void add_el_to_list(list_t **list, string value);

void free_list(list_t **list);

//void append(list_t **head_a, list_t **head_b);

list_t *create_hash_table(tree_node *root);

#endif // LIST_FUNCS_H
