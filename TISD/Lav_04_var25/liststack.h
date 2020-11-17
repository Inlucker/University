#ifndef LISTSTACK_H
#define LISTSTACK_H

#include "defines.h"

struct liststack
{
    char elem;
    //int id; // Для ограничения максимального кол-ва элементов
    liststack* previous_ptr;
};

liststack* create_liststack(char first_simbol);

void free_liststack(liststack **l);

liststack* add_liststack(char simbol, liststack *l);

liststack* input_liststack(string str);

bool is_liststack_empty(liststack *l);

char pop_liststack(liststack **l);

void print_liststack(liststack *l);

void print_liststack_status(liststack *l, int id);

int check_brackets_liststack(liststack *l);

#endif // LISTSTACK_H
