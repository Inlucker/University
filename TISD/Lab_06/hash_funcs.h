#ifndef HASH_FUNCS_H
#define HASH_FUNCS_H

#include "defines.h"
#include "structures.h"
#include "list_funcs.h"

int my_hash(string key, int m);

int my_hash2(string key, int m);

int make_simple(int n);

/*hash_table_t *create_table(int m);

hash_table_line_t *create_line(string value, int m);

void add_line_to_table(hash_table_t *table, string value);

void free_line(hash_table_line_t **line);

void free_table(hash_table_t **table);

void free_table(hash_table_line_t **table);

void get_table_from_tree(tree_node *root, hash_table_t *table, int *size, int m);

hash_table_t *create_hash_table(tree_node *root);

void print_hash_table(hash_table_t *table);*/

void fill_table_by_root(tree_node *root, int size, int m, list_t *table[], int hash_func(string, int));

void fill_hash_table(list_t *table[], int size, tree_node *root, int hash_func(string, int));

int print_hash_table(list_t *table[], int size);

void free_hash_table(list_t *table[], int size);

#endif // HASH_FUNCS_H
