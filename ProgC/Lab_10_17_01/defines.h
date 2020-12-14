#ifndef DEFINES_H
#define DEFINES_H

typedef struct node node_t;
typedef struct list list_t;

struct node
{
    void *data;
    node_t *next;
};

struct list
{
    node_t *head;
    node_t *tail;
};


#endif // DEFINES_H
