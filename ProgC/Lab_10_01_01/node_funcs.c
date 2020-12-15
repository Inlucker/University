#include "node_funcs.h"
#include "io_funcs.h"
#include <stdio.h>
#include <stdlib.h>

/*node_t* create(void *element)
{
    node_t *new_head = malloc(sizeof (node_t));
    new_head->data = element;
    new_head->next = NULL;
    return new_head;
}*/

/*void add(node_t **head, void *element)
{
    if (*head != NULL)
    {
        node_t *new_head = malloc(sizeof (node_t));
        new_head->data = element;
        new_head->next = *head;
        *head = new_head;
    }
    else
    {
        *head = create(element);
    }
}*/

void add(node_t **head, void *element)
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

void append(node_t **head_a, node_t **head_b)
{
    if (*head_a)
    {
        node_t *tmp_a = *head_a;
        while (tmp_a->next != NULL)
        {
            tmp_a = tmp_a->next;
        }
        tmp_a->next = *head_b;
        *head_b = NULL;
    }
    else
    {
        *head_a = *head_b;
        *head_b = NULL;
    }
}

/*void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *, const void *))
{
    if (head && element)
    {
        node_t *tmp = *head;
        if (tmp != NULL)
        {
            node_t *tmp2 = *head;
            tmp = tmp->next;
            while (tmp != NULL && comparator(element, tmp) > 0)
            {
                tmp = tmp->next;
                tmp2 = tmp2->next;
            }
            if (tmp2 == *head && comparator(element, tmp2) < 0)
            {
                element->next = tmp2;
                *head = element;
            }
            else
            {
                element->next = tmp;
                tmp2->next = element;
            }
        }
        else
        {
            *head = element;
            element->next = NULL;
        }
    }
}*/

void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *, const void *))
{
    if (*head == NULL)
    {
        element->next = NULL;
        *head = element;
    }
    else
    {
        node_t *tmp_n = (*head)->next;
        node_t *tmp_p = *head;
        while (tmp_n != NULL && comparator(element->data, tmp_n->data) > 0)
        {
            tmp_p = tmp_n;
            tmp_n = tmp_n->next;
        }

        if (tmp_p == *head && comparator(element->data, tmp_p->data) < 0)
        {
            element->next = *head;
            *head = element;
        }
        else
        {
            element->next = tmp_n;
            tmp_p->next = element;
        }
    }
}

node_t *sort(node_t *head, int (*comparator)(const void *, const void *))
{
    node_t *new_head = NULL;
    if (head)
    {
        node_t *tmp_el = head;
        while (tmp_el != NULL)
        {
            node_t *tmp_el2 = tmp_el;
            tmp_el = tmp_el->next;
            sorted_insert(&new_head, tmp_el2, comparator);
            //print_infos(new_head);
        }
    }
    return new_head;
}
