#ifndef TREE_FUNCS_H
#define TREE_FUNCS_H
#include "defines.h"
#include "structures.h"

tree_node *create_node(string value);

void add_node(tree_node *root, tree_node *node);

tree_node **search_word_in_tree(tree_node **root, string word, int *comp_counter);

uint64_t get_avg_search_time(tree_node *root, tree_node *cur_node, int *comp_counter);

void print_node_green(tree_node* root, int space, string word);

void print_searched_word_in_tree(tree_node* root, string word);

void print_node(tree_node* root, int space);

void print_tree(tree_node* root);

int count_nodes(tree_node *root);

tree_node *find_node_by_id(tree_node *root, int id, int *cur_id);

tree_node *get_new_root(tree_node *root);

void fill_root(tree_node *root, tree_node *tree, string root_value);

void balance_tree(tree_node **root);

void calculate_depth(tree_node *root, int *cur_depth);

/*void print_node_hash(tree_node *node, int m);

void print_tree_hashes(tree_node *root);*/

void delete_tree(tree_node **root);

#endif // TREE_FUNCS_H
