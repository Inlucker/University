#include "defines.h"
#include "listqueue.h"

#include <iostream>

using namespace std;

listqueue_element *create_listqueue_element()
{
    listqueue_element *new_listqueue_element = new listqueue_element;
    if (new_listqueue_element)
    {
        new_listqueue_element->next_ptr = NULL;
        new_listqueue_element->value = -1.0;
    }
    else
        new_listqueue_element = NULL;
    return new_listqueue_element;
}

listqueue *create_listqueue()
{
    listqueue *new_listqueue = new listqueue;
    if (new_listqueue)
    {
        listqueue_element *new_listqueue_element = create_listqueue_element();
        if (new_listqueue_element != NULL)
        {
            new_listqueue->ptr_in = new_listqueue_element;
            new_listqueue->ptr_out = new_listqueue_element;
        }
        else
        {
            free_listqueue(new_listqueue);
            new_listqueue = NULL;
        }
    }
    else
        new_listqueue = NULL;
    return new_listqueue;
}

bool is_list_empty(listqueue *queue)
{
    return (queue->ptr_in == queue->ptr_out);
}

void add_task(listqueue *queue, task t)
{
    queue->ptr_in->value = t;
    queue->ptr_in->next_ptr = create_listqueue_element();
    queue->ptr_in = queue->ptr_in->next_ptr;
}

task pop_task(listqueue *queue)
{
    task rez = queue->ptr_out->value;
    if (!is_list_empty(queue))
    {
        listqueue_element *ptr_to_delete = queue->ptr_out;
        queue->ptr_out = queue->ptr_out->next_ptr;
        delete ptr_to_delete;
    }
    return rez;
}

void free_listqueue(listqueue *queue)
{
    while (!is_list_empty(queue))
    {
        /*task tmp =*/ pop_task(queue);
        //cout << tmp << "; ";
    }
    //cout << endl;
    delete queue->ptr_out;
    delete queue;
}

void print_listqueue(listqueue *queue)
{
    listqueue_element *iterator = queue->ptr_out;
    int i = 0;
    while (iterator->next_ptr != NULL)
    {
        cout << "Ptr" << i << " = " << iterator << ": ";
        i++;
        cout << iterator->value << "; " << endl;
        iterator = iterator->next_ptr;
    }
    cout << endl;
}
