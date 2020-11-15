#include "defines.h"
#include "liststack.h"

liststack* create_liststack(char first_simbol)
{
    liststack *new_liststack = new liststack [1];
    new_liststack->elem = first_simbol;
    new_liststack->previous_ptr = NULL;
    return new_liststack;
}

void free_liststack(liststack **l)
{
    while(*l != NULL)
    {
        liststack *tmp = *l;
        //cout << tmp->elem << endl;
        //cout << tmp->previous_ptr << endl;
        *l = tmp->previous_ptr;
        free(tmp);
    }
    //cout << l << endl;
    //free(l);
}

liststack* add_liststack(char simbol, liststack *l)
{
    liststack *next_liststack = new liststack [1];
    next_liststack->elem = simbol;
    next_liststack->previous_ptr = l;
    return next_liststack;
}

char pop_liststack(liststack **l)
{
    liststack *tmp = *l;
    if (tmp == NULL)
    {
        cout << "ListStack is empty" << endl;
        return EMPTYSTACKERROR;
    }
    char rez = tmp->elem;
    if (tmp != NULL)
    {
        *l = tmp->previous_ptr;
    }
    free(tmp);
    return rez;
}

void print_liststack(liststack *l)
{
    //liststack *l = l;
    if (l != NULL)
    {
        //cout << "Liststack: " << endl;
        do
        {
            cout << l->elem;
            l = l->previous_ptr;
        }
        while (l != NULL);
        //cout << l->elem;
    }
    else
        cout << "This liststack is empty" << endl;
    cout << "\n" << endl;
}

void print_liststack_status(liststack *l)
{
    int i = 0;
    if (l != NULL)
    {
        do
        {
            cout << "Ptr" << i << ": " << l->previous_ptr << endl;
            l = l->previous_ptr;
            i++;
        }
        while (l != NULL);
    }
    else
        cout << "This liststack is empty" << endl;
    cout << "\n" << endl;
}

