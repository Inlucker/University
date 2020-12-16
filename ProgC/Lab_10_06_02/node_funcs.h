#ifndef NODE_FUNCS_H
#define NODE_FUNCS_H
#include "defines.h"

//void add(node_t **head, int r, int c, int v);

list_t *create_list(void);

void add(list_t **list, int r, int c, int v);

//void free_list(node_t **head);

void free_list(list_t **list);

void *pop_front(node_t **head);

void *pop_back(node_t **head);

#endif // NODE_FUNCS_H
