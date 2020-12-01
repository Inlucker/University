#ifndef MASQUEUE_H
#define MASQUEUE_H

#include "defines.h"

struct masqueue
{
    int id_in;
    int id_out;
    int size;
    int el_num;
    task* ptr;
};

masqueue *create_masqueue(int size);

bool is_full(masqueue *queue);

bool is_mas_empty(masqueue *queue);

int add_task(masqueue *queue, task t);

task pop_task(masqueue *queue);

void free(masqueue *queue);

void print_masqueue(masqueue *queue);

void print_masqueue_status(masqueue *queue);

#endif // MASQUEUE_H
