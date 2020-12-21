#ifndef LIST_FUNCS_H
#define LIST_FUNCS_H

#include "defines.h"
#include "structures.h"

//list_t *create_list(string value);

void add_el_to_list(list_t **list, string value);

void free_list(list_t **list);

#endif // LIST_FUNCS_H
