#ifndef IO_FUNCS_H
#define IO_FUNCS_H
#include "structures.h"
#include "defines.h"

tree_node *read_file(string file_name);

int search_word_in_file(string file_name, string word);

int get_file_size(string file_name);

#endif // IO_FUNCS_H
