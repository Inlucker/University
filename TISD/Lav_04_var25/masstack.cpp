#include "masstack.h"

masstack malloc_masstack(int size)
{
    masstack new_massstack;
    new_massstack.capacity = size;
    new_massstack.mas = new char [new_massstack.capacity];
    new_massstack.cur_ptr = new_massstack.mas;
    return new_massstack;
}

void free_masstack(masstack *m)
{
    delete [] m->mas;
}

int add_masstack(char simbol, masstack *m)
{
    if (m->cur_ptr - m->mas + 1 > m->capacity)
    {
        cout << "OverflowError" << endl;
        return OVERFLOW_ERROR;
    }
    *(m->cur_ptr) = simbol;
    m->cur_ptr++;
    return 0;
}

bool is_masstack_full(masstack m)
{
    return m.cur_ptr - m.mas + 1 > m.capacity;
}

masstack input_masstack(string str, int capacity)
{
    int tmp = capacity;
    if (tmp < str.length())
        tmp = str.length();
    masstack new_masstack = malloc_masstack(capacity);
    for (int i = 0; i < str.length(); i++)
    {
        if (add_masstack(str[i], &new_masstack) != 0)
        {
            cout << "Input Error" << endl;
            return new_masstack;
        }
    }
    return new_masstack;
}

bool is_masstack_empty(masstack m)
{
    return m.cur_ptr <= m.mas;
}

char pop_masstack(masstack *m)
{
    if (is_masstack_empty(*m))
    {
        cout << "This mas_stack is empty" << endl;
        return EMPTY_STACK_ERROR;
    }
    m->cur_ptr--;

    return *(m->cur_ptr);
}

void print_masstack(masstack m)
{
    char *i = m.cur_ptr - 1;
    while (i >= m.mas)
    {
        cout << *i; // << " ";
        i--;
    }
    cout << "\n" << endl;
}

void print_masstack_status(masstack m)
{
    cout << "Starting ptr: " << (void*)m.mas << endl;
    cout << "Current ptr: " << (void*)m.cur_ptr << endl;
    cout << "Capacity: " << m.cur_ptr - m.mas << "/" << m.capacity << endl;
    cout << "Top border: " << (void*)(m.mas + m.capacity) << endl;
    cout << endl;
    //printf("Starting ptr: %p\nCurrent ptr: %p\nCapacity: %d/%d\nTop border: %p\n\n", m.mas, m.cur_ptr, m.cur_ptr - m.mas, m.capacity, m.mas + m.capacity);
}

int check_brackets_masstack(masstack m)
{
    string str = "";
    char *i = m.cur_ptr - 1;
    while (i >= m.mas)
    {
        str += *i; // << " ";
        i--;
    }
    //cout << str << endl;

    int brackets[3] = {0, 0, 0};
    masstack lastbrackets = malloc_masstack(str.length());
    for (int i = str.length() - 1; i >= 0; i--)
    {
        if (str[i] == '(')
        {
            brackets[0]++;
            if (add_masstack(str[i], &lastbrackets) != 0)
            {
                return CHECK_ERROR;
            }
        }
        else if (str[i] == '{')
        {
            brackets[1]++;
            if (add_masstack(str[i], &lastbrackets) != 0)
            {
                return CHECK_ERROR;
            }
        }
        else if (str[i] == '[')
        {
            brackets[2]++;
            if (add_masstack(str[i], &lastbrackets) != 0)
            {
                return CHECK_ERROR;
            }
        }
        else if (str[i] == ')')
        {
            if (is_masstack_empty(lastbrackets))
                return 0;
            if (pop_masstack(&lastbrackets) != '(')
                return 0;
            brackets[0]--;
        }
        else if (str[i] == '}')
        {
            if (is_masstack_empty(lastbrackets))
                return 0;
            if (pop_masstack(&lastbrackets) != '{')
                return 0;
            brackets[1]--;
        }
        else if (str[i] == ']')
        {
            if (is_masstack_empty(lastbrackets))
                return 0;
            if (pop_masstack(&lastbrackets) != '[')
                return 0;
            brackets[2]--;
        }
    }

    if (brackets[0] == 0 && brackets[1] == 0 && brackets[2] == 0)
        return 1;
    else
        return 0;
}
