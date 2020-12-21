#include "list_funcs.h"
#include "tree_funcs.h"
#include "hash_funcs.h"

void add_el_to_list(list_t **head, string value)
{
    list_t *new_head = new list_t;
    new_head->value = value;
    new_head->next = *head;
    *head = new_head;
}

void free_list(list_t **list)
{
    list_t *tmp = *list;
    while (tmp)
    {
        list_t *ptr_to_delete = tmp;
        tmp = tmp->next;
        delete ptr_to_delete;
    }
    *list = NULL;
}

/*(void append(list_t **head_a, list_t **head_b)
{
    if (*head_a)
    {
        list_t *tmp_a = *head_a;
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
}*/
