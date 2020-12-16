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

node_t *find_row(node_t *head, int r)
{
    while (head && head->data->row != r)
    {
        head = head->next;
    }
    return head;
}

node_t *find_column(node_t *head, int c)
{
    while (head && head->data->column != c)
    {
        head = head->next;
    }
    return head;
}

int find_max_row(node_t *head)
{
    int rez = -1;
    while (head)
    {
        if (head->data->row > rez)
            rez = head->data->row;
        head = head->next;
    }
    return rez;
}

int find_max_column(node_t *head)
{
    int rez = -1;
    while (head)
    {
        if (head->data->column > rez)
            rez = head->data->column;
        head = head->next;
    }
    return rez;
}

list_t *compostion(list_t *list1, list_t *list2)
{
    list_t *rez = NULL;

    if (list1 && list2)
    {
        int i = 0, j = 0;
        rez = create_list();
        node_t *it1 = list1->head;
        node_t *it2 = list2->head;
        int i_max = find_max_row(it1) + 1;
        int j_max = find_max_row(it2) + 1;

        while (i < i_max && j < j_max)
        {
            int tmp_value = 0;

            if ((it1 && it1->data->row == i) && (it2 && it2->data->column == j))
            {
                node_t *it1_1 = it1;
                node_t *it2_2 = it2;
                while ((it1_1 && it1_1->data->row == i) && (it2_2 && it2_2->data->column == j))
                {
                    if (it1_1->data->column == it2_2->data->row)
                    {
                        tmp_value += it1_1->data->value * it2_2->data->value;
                        it1_1 = it1_1->next;
                        while (it1_1 && it1_1->data->row != i)
                            it1_1 = it1_1->next;
                        it2_2 = it2_2->next;
                        while (it2_2 && it2_2->data->column != j)
                            it2_2 = it2_2->next;
                    }
                    else if (it1_1->data->column > it2_2->data->row)
                    {
                        it2_2 = it2_2->next;
                        while (it2_2 && it2_2->data->column != j)
                            it2_2 = it2_2->next;
                    }
                    else if (it1_1->data->column < it2_2->data->row)
                    {
                        it1_1 = it1_1->next;
                        while (it1_1 && it1_1->data->row != i)
                            it1_1 = it1_1->next;
                    }
                }
            }

            if (tmp_value != 0)
            {
                add(&rez, i, j, tmp_value);
            }
            j++;

            if (j >= j_max)
            {
                i++;
                if (i >= i_max)
                    break;
                j = 0;

                node_t *it1_1 = find_row(list1->head, i);
                while (i < i_max && !it1_1)
                {
                    i++;
                    it1_1 = find_row(list1->head, i);
                }
                it1 = it1_1;
            }

            node_t *it2_2 = find_column(list2->head, j);
            while (j < j_max && !it2_2)
            {
                j++;
                it2_2 = find_column(list2->head, j);
            }
            it2 = it2_2;
        }
    }
    return rez;
}


