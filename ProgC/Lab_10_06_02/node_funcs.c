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

list_t *addition(list_t *list1, list_t *list2)
{
    list_t *rez = NULL;

    if (list1 && list2)
    {
        int i = 0, j = 0;
        rez = create_list();
        node_t *it1 = list1->head;
        node_t *it2 = list2->head;

        while (it1 || it2)
        {
            if ((it1 && it1->data->column == j && it1->data->row == i) && (it2 && it2->data->column == j && it2->data->row == i))
            {
                add(&rez, i, j, it1->data->value + it2->data->value);
                it1 = it1->next;
                it2 = it2->next;
            }
            else if (it1 && it1->data->column == j && it1->data->row == i)
            {
                add(&rez, i, j, it1->data->value);
                it1 = it1->next;
            }
            else if (it2 && it2->data->column == j && it2->data->row == i)
            {
                add(&rez, i, j, it2->data->value);
                it2 = it2->next;
            }
            j++;
            if ((!it1 || it1->data->row > i) && (!it2 || it2->data->row > i))
            {
                i++;
                j = 0;
            }
        }
    }
    return rez;
}
