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

list_t *addition(list_t *list1, list_t *list2);

node_t *find_row(node_t *head, int r);

node_t *find_column(node_t *head, int c);

int find_max_row(node_t *head);

int find_max_column(node_t *head);

list_t *compostion(list_t *list1, list_t *list2);

void *delete_max_line(list_t *list);

#endif // NODE_FUNCS_H
