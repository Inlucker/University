#include "node_funcs.h"
#include <stdio.h>

void* pop_front(node_t **head)
{
    void *rez = (*head)->data;
    *head = (*head)->next;
    return rez;
}

void* pop_back(node_t **head)
{
    node_t *tmp = *head;
    while (tmp->next != NULL)
    {
        tmp = tmp->next;
    }
    void *rez = tmp->data;
    return rez;
}

void append(node_t **head_a, node_t **head_b)
{

}

void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *, const void *))
{

}
