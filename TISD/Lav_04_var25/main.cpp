#include "defines.h"
#include "masstack.h"

struct liststack
{
    char elem;
    liststack* previous_ptr;
};

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
        cout << "EmptyStackError" << endl;
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

int main()
{
    char c = 'a';
    char test = '-';
    liststack *l1 = create_liststack(c);

    /*test = pop_liststack(&l1);
        if (test != EMPTYSTACKERROR)
            cout << "poped: " << test << endl;*/

    c++;
    for (int i = 0; i < 25; i++)
    {
        l1 = add_liststack(c, l1);
        c++;
    }

    print_liststack(l1);
    //print_liststack_status(l1);

    for (int i = 0; i < 3; i++)
    {
        test = pop_liststack(&l1);
        if (test != EMPTYSTACKERROR)
            cout << "poped: " << test << endl;
    }

    print_liststack(l1);
    //print_liststack_status(l1);

    //print_liststack(l1);

    masstack m1 = malloc_masstack(26);
    c = 'a';
    for (int i = 0; i < 26; i++)
    {
        if (add_masstack(c, &m1) != 0)
        {
            break;
        }
        c++;
    }

    print_masstack(m1);
    print_masstack_status(m1);

    for (int i = 0; i < 3; i++)
    {
        test = pop_masstack(&m1);
        if (test != EMPTYSTACKERROR)
            cout << "poped: " << test << endl;
    }

    print_masstack(m1);
    print_masstack_status(m1);

    free_liststack(&l1);
    free_masstack(&m1);
    return 0;
}
