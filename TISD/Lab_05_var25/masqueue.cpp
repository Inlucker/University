#include "defines.h"
#include "masqueue.h"

masqueue create_masqueue(int size)
{
    masqueue new_queue;
    new_queue.ptr = new my_type [size];
    if (!new_queue.ptr)
    {
        new_queue.size = -1;
    }
    else
    {
        new_queue.id_in = 1;
        new_queue.id_out = 1;
        new_queue.el_num = 0;
        new_queue.size = size;
    }
    return new_queue;
}

bool is_full(masqueue queue)
{
    return (queue.el_num == queue.size);
}

bool is_mas_empty(masqueue queue)
{
    return (queue.el_num == 0);
}

int add_task(masqueue *queue, my_type task)
{
    if (is_full(*queue))
    {
        return OVERFLOW_ERROR;
    }
    *(queue->ptr + queue->id_in) = task;
    queue->id_in++;
    queue->el_num++;
    if (queue->id_in > queue->size)
        queue->id_in = 1;
    return OK;
}

my_type pop_task(masqueue *queue)
{
    my_type rez = -1.0;
    if (!is_mas_empty(*queue))
    {
        rez = *(queue->ptr + queue->id_out);
        queue->id_out++;
        queue->el_num--;
        if (queue->id_out > queue->size)
            queue->id_out = 1;
    }
    return rez;
}

void print_masqueue_status(masqueue queue)
{
    cout << "Queue size: " << queue.size << endl;
    cout << "Queue id_in: " << queue.id_in << endl;
    cout << "Queue id_out: " << queue.id_out << endl;
    cout << "Queue elements number: " << queue.el_num << endl;
    cout << "Queue start_ptr: " << queue.ptr << endl;

}
