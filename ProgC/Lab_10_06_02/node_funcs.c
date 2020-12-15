#include "node_funcs.h"
#include "io_funcs.h"
#include <stdio.h>
#include <stdlib.h>

void add(node_t **head, elem_t *element)
{
    node_t *new_head = malloc(sizeof (node_t));
    new_head->data = element;
    new_head->next = *head;
    *head = new_head;
}

void free_list(node_t **head)
{
    if (*head != NULL)
    {
        node_t *tmp = *head;
        node_t *ptr_to_free = tmp;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
            free(ptr_to_free->data);
            free(ptr_to_free);
            ptr_to_free = tmp;
        }
        if (tmp->data)
            free(tmp->data);
        if (tmp)
            free(tmp);
        *head = NULL;
    }
}

void *pop_front(node_t **head)
{
    void *rez = NULL;
    if (head && *head)
    {
        rez = (*head)->data;
        node_t *ptr_to_free = *head;
        *head = (*head)->next;
        free(ptr_to_free);
    }
    return rez;
}

void *pop_back(node_t **head)
{
    void *rez = NULL;
    if (head && *head)
    {
        node_t *tmp = *head;
        if (tmp->next != NULL)
        {
            node_t *new_tail = tmp;
            tmp = tmp->next;
            while (tmp->next != NULL)
            {
                tmp = tmp->next;
                new_tail = new_tail->next;
            }
            rez = tmp->data;
            node_t *ptr_to_free = tmp;
            free(ptr_to_free);
            new_tail->next = NULL;
        }
        else
        {
            rez = tmp->data;
            free(tmp);
            *head = NULL;
        }
    }
    return rez;
}
