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

liststack* input_liststack(string str)
{
    liststack *new_liststack = NULL;
    for (int i = 0; i < str.length(); i++)
    {
        new_liststack = add_liststack(str[i], new_liststack);
    }
    return new_liststack;
}

bool is_liststack_empty(liststack *l)
{
    return (l == NULL);
}

char pop_liststack(liststack **l)
{
    liststack *tmp = *l;
    if (tmp == NULL)
    {
        cout << "ListStack is empty" << endl;
        return EMPTY_STACK_ERROR;
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

int check_brackets_liststack(liststack *l)
{
    string str = "";
    //liststack *l = l;
    if (l != NULL)
    {
        //cout << "Liststack: " << endl;
        do
        {
            str += l->elem;
            l = l->previous_ptr;
        }
        while (l != NULL);
        //cout << l->elem;
    }
    else
        cout << "This liststack is empty" << endl;

    //cout << str << endl;

    int brackets[3] = {0, 0, 0};
    liststack *lastbrackets = NULL;
    for (int i = str.length() - 1; i >= 0; i--)
    {
        if (str[i] == '(')
        {
            brackets[0]++;
            lastbrackets = add_liststack(str[i], lastbrackets);
        }
        else if (str[i] == '{')
        {
            brackets[1]++;
            lastbrackets = add_liststack(str[i], lastbrackets);
        }
        else if (str[i] == '[')
        {
            brackets[2]++;
            lastbrackets = add_liststack(str[i], lastbrackets);
        }
        else if (str[i] == ')')
        {
            if (is_liststack_empty(lastbrackets))
            {
                free_liststack(&lastbrackets);
                return 0;
            }
            if (pop_liststack(&lastbrackets) != '(')
            {
                free_liststack(&lastbrackets);
                return 0;
            }
            brackets[0]--;
        }
        else if (str[i] == '}')
        {
            if (is_liststack_empty(lastbrackets))
            {
                free_liststack(&lastbrackets);
                return 0;
            }
            if (pop_liststack(&lastbrackets) != '{')
            {
                free_liststack(&lastbrackets);
                return 0;
            }
            brackets[1]--;
        }
        else if (str[i] == ']')
        {
            if (is_liststack_empty(lastbrackets))
            {
                free_liststack(&lastbrackets);
                return 0;
            }
            if (pop_liststack(&lastbrackets) != '[')
            {
                free_liststack(&lastbrackets);
                return 0;
            }
            brackets[2]--;
        }
    }

    if (brackets[0] == 0 && brackets[1] == 0 && brackets[2] == 0)
        return 1;
    else
        return 0;
}
