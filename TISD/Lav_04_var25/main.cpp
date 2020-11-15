#include "defines.h"
#include "masstack.h"
#include "liststack.h"

int main()
{
    char c = 'a';
    char test = '-';
    liststack *l1 = create_liststack(c);
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
