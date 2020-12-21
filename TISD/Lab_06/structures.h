#ifndef STRUCTURES_H
#define STRUCTURES_H
#include "defines.h"

struct list_t
{
    string value;
    list_t *next;
};

struct tree_node
{
    string value;
    tree_node *left;
    tree_node *right;
};

#endif // STRUCTURES_H
