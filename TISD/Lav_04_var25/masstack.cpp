#include "defines.h"
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
        return OVERFLOWERROR;
    }
    *(m->cur_ptr) = simbol;
    m->cur_ptr++;
    return 0;
}

char pop_masstack(masstack *m)
{
    if (m->cur_ptr <= m->mas )
    {
        cout << "EmptyStackError" << endl;
        return EMPTYSTACKERROR;
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
