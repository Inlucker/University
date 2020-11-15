#ifndef MASSTACK_H
#define MASSTACK_H

struct masstack
{
    char *mas;
    char *cur_ptr;
    int capacity;
};

masstack malloc_masstack(int size);

void free_masstack(masstack *m);

int add_masstack(char simbol, masstack *m);

char pop_masstack(masstack *m);

void print_masstack(masstack m);

void print_masstack_status(masstack m);

#endif // MASSTACK_H
