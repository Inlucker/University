#ifndef TREE_FUNCS_H
#define TREE_FUNCS_H
#include "defines.h"
#include "structures.h"

tree_node *create_node(string value);

void add_node(tree_node *root, tree_node *node);

tree_node *search_node(tree_node *root, int value);

void print_tree(tree_node* root, int space);

void delete_tree(tree_node *root);

#endif // TREE_FUNCS_H
