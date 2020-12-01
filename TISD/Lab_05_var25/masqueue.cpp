#include "defines.h"
#include "masqueue.h"

#include <iostream>

using namespace std;

masqueue *create_masqueue(int size)
{
    masqueue *new_queue = new masqueue;
    if (new_queue)
    {
        new_queue->ptr = new task[size];
        if (new_queue->ptr)
        {
            new_queue->id_in = 0;
            new_queue->id_out = 0;
            new_queue->el_num = 0;
            new_queue->size = size;
        }
        else
        {
            free(new_queue);
            new_queue = NULL;
        }
    }
    else
        new_queue = NULL;
    return new_queue;
}

bool is_full(masqueue *queue)
{
    return (queue->el_num == queue->size);
}

bool is_mas_empty(masqueue *queue)
{
    return (queue->el_num == 0);
}

int add_task(masqueue *queue, task t)
{
    if (is_full(queue))
    {
        return OVERFLOW_ERROR;
    }
    *(queue->ptr + queue->id_in) = t;
    queue->id_in++;
    queue->el_num++;
    if (queue->id_in >= queue->size)
        queue->id_in = 0;
    return OK;
}

task pop_task(masqueue *queue)
{
    task rez = -1.0;
    if (!is_mas_empty(queue))
    {
        rez = *(queue->ptr + queue->id_out);
        queue->id_out++;
        queue->el_num--;
        if (queue->id_out >= queue->size)
            queue->id_out = 0;
    }
    return rez;
}

void free(masqueue *queue)
{
    delete[] queue->ptr;
    delete queue;
}

void print_masqueue(masqueue *queue)
{
    int i = queue->id_out;
    int elems = queue->el_num;
    for (int j = elems; j > 0; j--)
    {
        cout << *(queue->ptr + i) << "; ";
        i++;
        if (i >= queue->size)
            i = 0;
    }
    cout << endl;
}

void print_masqueue_status(masqueue *queue)
{
    cout << "Queue size: " << queue->size << endl;
    cout << "Queue id_in: " << queue->id_in << endl;
    cout << "Queue id_out: " << queue->id_out << endl;
    cout << "Queue elements number: " << queue->el_num << endl;
    cout << "Queue start_ptr: " << queue->ptr << endl;
}
