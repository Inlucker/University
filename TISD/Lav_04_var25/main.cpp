#include "defines.h"
#include "masstack.h"
#include "liststack.h"

int main()
{
    cout << sizeof (liststack) << endl;
    cout << "Hi" << endl;
    srand(time(0));

    masstack mas_stack = malloc_masstack(26);
    for (int i = 0; i < 26; i++)
    {
        if (add_masstack('a' + i, &mas_stack) != 0)
        {
            break;
        }
    }

    //print_masstack(m1);
    //print_masstack_status(m1);

    liststack *list_stack = create_liststack('a');
    for (int i = 0; i < 25; i++)
    {
        list_stack = add_liststack('a' + 1 + i, list_stack);
    }

    //print_liststack(l1);
    //print_liststack_status(l1);

    int input = -1;

    //cout << sizeof (car) << " " << sizeof (price_keys) << endl;

    while (input != 0)
    {
        cout << endl;
        cout << "Mas_stack commands:" << endl;
        cout << " 1 - Input mas_stack" << endl;
        cout << " 2 - Print mas_stack" << endl;
        cout << " 3 - Add symbol to mas_stack" << endl;
        cout << " 4 - Pop symbol from mas_stack" << endl;
        cout << " 5 - Print mas_stack status" << endl;
        cout << " 6 - Check mas_stack brackets" << endl;
        cout << "List_stack commands:" << endl;
        cout << " 7 - Input list_stack" << endl;
        cout << " 8 - Print list_stack" << endl;
        cout << " 9 - Add symbol to list_stack" << endl;
        cout << "10 - Pop symbol from list_stack" << endl;
        cout << "11 - Print list_stack status" << endl;
        cout << "12 - Check list_stack brackets" << endl;
        cout << "Compare commands:" << endl;
        cout << "13 - Compare work time for mas_stack and list_stack" << endl;
        cout << "14 - Compare memory for mas_stack and list_stack" << endl;
        cout << "0 - Exit from programm\n" << endl;

        _flushall();
        cout << "Enter the number of command to be done: ";
        while (!(cin >> input))
        {
            cout << "Wrong input" << endl;
            cin.clear();
            _flushall();
            cout << "Enter the number of command to be done: ";
        }

        switch (input)
        {
        case 1:
        {
            _flushall();
            cout << "Enter the expression: ";
            string inp;
            cin >> inp;
            _flushall();
            cout << "Enter the capacity: ";
            int cap;
            cin >> cap;
            if (cap < inp.length())
            {
                cout << "Wrong input - capacity is smaller than expression length" << endl;
                break;
            }
            mas_stack = input_masstack(inp, cap);
            break;
        }
        case 2:
        {
            print_masstack(mas_stack);
            break;
        }
        case 3:
        {
            if (is_masstack_full(mas_stack))
            {
                cout << "This mas_stack is full" << endl;
                break;
            }
            _flushall();
            cout << "Enter the symbol to add: ";
            char inp;
            cin >> inp;
            if (add_masstack(inp, &mas_stack) != 0)
            {
                break;
            }
            break;
        }
        case 4:
        {
            char symbol = pop_masstack(&mas_stack);
            if (symbol != EMPTY_STACK_ERROR)
            {
                cout << "Poped: " << symbol << endl;
            }
            break;
        }
        case 5:
        {
            print_masstack_status(mas_stack);
            break;
        }
        case 6:
        {
            if (is_masstack_empty(mas_stack))
            {
                cout << "This mas_stack is empty" << endl;
                break;
            }
            int rez = check_brackets_masstack(mas_stack);
            if (rez == 1)
                cout << "Brackets in mas_stack are ok" << endl;
            else if (rez == 0)
                cout << "Brackets in mas_stack are not ok" << endl;
            else
                cout << "ERROR" << endl;
            break;
        }
        case 7:
        {
            _flushall();
            cout << "Enter the expression: ";
            string inp;
            cin >> inp;
            list_stack = input_liststack(inp);
            break;
        }
        case 8:
        {
            print_liststack(list_stack);
            break;
        }
        case 9:
        {
            _flushall();
            cout << "Enter the symbol to add: ";
            char inp;
            cin >> inp;
            list_stack = add_liststack(inp, list_stack);
            break;
        }
        case 10:
        {
            liststack *adr = list_stack;
            char symbol = pop_liststack(&list_stack);
            if (symbol != EMPTY_STACK_ERROR)
            {
                cout << "Adress: " << adr << endl;
                cout << "Poped: " << symbol << endl;
            }
            break;
        }
        case 11:
        {
            print_liststack_status(list_stack);
            break;
        }
        case 12:
        {
            int rez = check_brackets_liststack(list_stack);
            if (rez == 1)
                cout << "Brackets in list_stack are ok" << endl;
            else if (rez == 0)
                cout << "Brackets in list_stack are not ok" << endl;
            else
                cout << "ERROR" << endl;
            break;
        }
        case 13:
        {
            _flushall();
            cout << "Enter the iterations: ";
            int iterations;
            cin >> iterations;
            masstack mas_stack1 = malloc_masstack(10000);
            for (int i = 0; i < 10000; i++)
            {
                if (add_masstack(i, &mas_stack1) != 0)
                {
                    break;
                }
            }

            clock_t start = clock();
            for (int i = 0; i < iterations; i++)
                check_brackets_masstack(mas_stack1);
            clock_t end = clock();
            double seconds = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Check_brackets_masstack test time: %.4f seconds\n", seconds);

            free_masstack(&mas_stack1);

            liststack *list_stack1 = create_liststack('a');
            for (int i = 0; i < 10000; i++)
            {
                list_stack1 = add_liststack('a' + 1 + i, list_stack1);
            }

            start = clock();
            for (int i = 0; i < iterations; i++)
                check_brackets_liststack(list_stack1);
            end = clock();
            seconds = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Check_brackets_liststack test time: %.4f seconds\n", seconds);

            free_liststack(&list_stack1);

            break;
        }
        case 14:
        {
            _flushall();
            cout << "Enter the number of elements: ";
            int elems;
            cin >> elems;
            if (elems > 0)
            {
                cout << "Mas_stack: " << elems * sizeof(char) + 2 * sizeof(char*) + sizeof (int) << " bytes." << endl;
                cout << "List_stack: " << elems * (sizeof(char) + sizeof(liststack*)) << " bytes." << endl;
            }
            else
                cout << "Wrong input" << endl;

            break;
        }
        default:
            cout << "Wrong command" << endl;
            break;
        }
    }

    free_masstack(&mas_stack);
    free_liststack(&list_stack);
    return 0;
}
