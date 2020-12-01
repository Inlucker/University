#ifndef LISTQUEUE_H
#define LISTQUEUE_H

#include "defines.h"


struct listqueue_element
{
    task value;
    listqueue_element* next_ptr;
};

struct listqueue
{
    listqueue_element *ptr_in;
    listqueue_element *ptr_out;
};

listqueue_element *create_listqueue_element();

listqueue *create_listqueue();

bool is_list_empty(listqueue *queue);

void add_task(listqueue *queue, task t);

task pop_task(listqueue *queue);

void free(listqueue *queue);

void print_listqueue(listqueue *queue);

#endif // LISTQUEUE_H
