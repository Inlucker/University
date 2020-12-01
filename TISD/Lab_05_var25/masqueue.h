#ifndef MASQUEUE_H
#define MASQUEUE_H

#define my_type double

struct masqueue
{
    int id_in;
    int id_out;
    int size;
    int el_num;
    my_type* ptr;
};

masqueue create_masqueue(int size);

bool is_full(masqueue queue);

bool is_mas_empty(masqueue queue);

int add_task(masqueue *queue, my_type task);

my_type pop_task(masqueue *queue);

void print_masqueue_status(masqueue queue);

#endif // MASQUEUE_H
