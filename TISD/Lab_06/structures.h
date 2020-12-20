#ifndef STRUCTURES_H
#define STRUCTURES_H

struct list
{
    int value;
    list *next;
};

struct node
{
    int value;
    node *left;
    node *right;
};

#endif // STRUCTURES_H
