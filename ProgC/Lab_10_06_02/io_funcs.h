#ifndef IO_FUNCS_H
#define IO_FUNCS_H

#include "defines.h"

list_t *read_file(char *file_name);

list_t *read_mtrx(void);

void print_node(node_t *head);

void print_list(list_t *list);

#endif // IO_FUNCS_H
