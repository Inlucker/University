#ifndef LISTSTACK_H
#define LISTSTACK_H

struct liststack
{
    char elem;
    liststack* previous_ptr;
};

liststack* create_liststack(char first_simbol);

void free_liststack(liststack **l);

liststack* add_liststack(char simbol, liststack *l);

char pop_liststack(liststack **l);

void print_liststack(liststack *l);

void print_liststack_status(liststack *l);

#endif // LISTSTACK_H
