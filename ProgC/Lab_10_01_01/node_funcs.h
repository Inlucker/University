#ifndef NODE_FUNCS_H
#define NODE_FUNCS_H
#include "defines.h"

//node_t* create(void *element);

void add(node_t **head, void *element);

void free_list(node_t **head);

void *pop_front(node_t **head);

void *pop_back(node_t **head);

void append(node_t **head_a, node_t **head_b);

void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *, const void *));

node_t *sort(node_t *head, int (*comparator)(const void *, const void *));

#endif // NODE_FUNCS_H
