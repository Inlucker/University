#include "node_funcs.h"
#include "io_funcs.h"
#include <stdio.h>
#include <stdlib.h>

/*void add(node_t **head, int r, int c, int v)
{
    node_t *new_head = malloc(sizeof (node_t));
    elem_t *tmp_elem = malloc(sizeof (elem_t));
    tmp_elem->row = r;
    tmp_elem->column = c;
    tmp_elem->value = v;
    new_head->data = tmp_elem;
    new_head->next = *head;
    *head = new_head;
}*/

list_t *create_list()
{
    list_t *new_list = malloc(sizeof (list_t));
    new_list->head = NULL;
    new_list->tail = NULL;
    return new_list;
}

void add(list_t **list, int r, int c, int v)
{
    node_t *new_tail = malloc(sizeof (node_t));
    elem_t *tmp_elem = malloc(sizeof (elem_t));
    tmp_elem->row = r;
    tmp_elem->column = c;
    tmp_elem->value = v;
    new_tail->data = tmp_elem;
    if (!(*list)->head)
        (*list)->head = new_tail;
    if ((*list)->tail)
        (*list)->tail->next = new_tail;
    (*list)->tail = new_tail;
    new_tail->next = NULL;
}

/*void free_list(node_t **head)
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
}*/

void free_list(list_t **list)
{
    if ((*list)->head && *list)
    {
        node_t *tmp = (*list)->head;
        node_t *ptr_to_free = tmp;
        while (tmp->next != NULL)
        {
            tmp = tmp->next;
            free(ptr_to_free->data);
            free(ptr_to_free);
            ptr_to_free = tmp;
        }
        free(tmp->data);
        free(tmp);
        (*list)->head = NULL;
        (*list)->tail = NULL;
        free(*list);
        *list = NULL;
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
