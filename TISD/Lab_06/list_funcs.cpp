#include "list_funcs.h"

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
