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
            free(ptr_to_free);
            ptr_to_free = tmp;
        }
        free(tmp);
        *head = NULL;
    }
}

void* pop_front(node_t **head)
{
    void *rez = (*head)->data;
    node_t *ptr_to_free = *head;
    *head = (*head)->next;
    free(ptr_to_free);
    return rez;
}

void* pop_back(node_t **head)
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
        void *rez = tmp->data;
        node_t *ptr_to_free = tmp;
        free(ptr_to_free);
        new_tail->next = NULL;
        return rez;
    }
    else
    {
        void *rez = tmp->data;
        free(tmp);
        return rez;
    }
}

void append(node_t **head_a, node_t **head_b)
{
    node_t *tmp_a = *head_a;
    while (tmp_a->next != NULL)
    {
        tmp_a = tmp_a->next;
    }
    tmp_a->next = *head_b;
    *head_b = NULL;
}

void sorted_insert(node_t **head, node_t *element, int (*comparator)(const void *, const void *))
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
        if (tmp2 != *head || comparator(element, tmp2) > 0)
        {
            element->next = tmp;
            tmp2->next = element;
        }
        else
        {
            element->next = tmp2;
            *head = element;
        }
    }
    else
    {
        *head = element;
        element->next = NULL;
    }
}

void sort(node_t **head, int (*comparator)(const void *, const void *))
{
    node_t *new_head = NULL;
    node_t *tmp_el = *head;
    while (tmp_el != NULL)
    {
        node_t *tmp_el2 = tmp_el;
        tmp_el = tmp_el->next;
        sorted_insert(&new_head, tmp_el2, comparator);
        //print_infos(new_head);
    }
    *head = new_head;
}
