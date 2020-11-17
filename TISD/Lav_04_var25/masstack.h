#ifndef MASSTACK_H
#define MASSTACK_H

#include "defines.h"

struct masstack
{
    char *mas;
    char *cur_ptr;
    int capacity;
};

masstack malloc_masstack(int size);

void free_masstack(masstack *m);

int add_masstack(char simbol, masstack *m);

bool is_masstack_full(masstack m);

masstack input_masstack(string str, int capacity);

bool is_masstack_empty(masstack m);

char pop_masstack(masstack *m);

void print_masstack(masstack m);

void print_masstack_status(masstack m);

int check_brackets_masstack(masstack m);

#endif // MASSTACK_H
