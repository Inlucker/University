#ifndef HASH_FUNCS_H
#define HASH_FUNCS_H

#include "defines.h"
#include "structures.h"
#include "list_funcs.h"

int my_hash(string key, int m);

hash_table_t *create_table(int m);

hash_table_line_t *create_line(string value, int m);

void add_line_to_table(hash_table_t *table, string value);

void free_line(hash_table_line_t **line);

void free_table(hash_table_t **table);

void free_table(hash_table_line_t **table);

#endif // HASH_FUNCS_H
