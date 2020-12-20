#ifndef STRUCTURES_H
#define STRUCTURES_H
#include "defines.h"

struct list
{
    string value;
    list *next;
};

struct tree_node
{
    string value;
    tree_node *left;
    tree_node *right;
};

#endif // STRUCTURES_H
