#ifndef NODE_FUNCS_H
#define NODE_FUNCS_H
#include "defines.h"

void add(node_t **head, elem_t *element);

void free_list(node_t **head);

void *pop_front(node_t **head);

void *pop_back(node_t **head);

#endif // NODE_FUNCS_H
