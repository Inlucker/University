#ifndef IO_FUNCS_H
#define IO_FUNCS_H
#include "structures.h"
#include "defines.h"

tree_node *read_file(string file_name);

int search_word_in_file(string file_name, string word);

#endif // IO_FUNCS_H
