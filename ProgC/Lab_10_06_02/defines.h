#ifndef DEFINES_H
#define DEFINES_H

#define N 4
#define EPS 1e-7

#define ARGS_ERROR -1
#define INPUT_ERROR -2

typedef struct node node_t;
typedef struct elem elem_t;
typedef struct list list_t;

struct elem
{
    int row;
    int column;
    int value;
};

struct node
{
    elem_t *data;
    node_t *next;
};

struct list
{
    node_t *head;
    node_t *tail;
};


#endif // DEFINES_H
