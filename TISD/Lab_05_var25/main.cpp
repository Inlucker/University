#include "defines.h"
#include "masqueue.h"
#include "listqueue.h"

int main()
{
    cout << "Hello World!" << endl;
    srand(time(0));

    //cout << rand() % 5 + 1 << endl; // 1-5

    if (rand() % 2 == 0) //first type
    {

    }


    masqueue mq = create_masqueue(10);

    for (int i = 0; i < 10; i++)
    {
        if (add_task(&mq, (double)i) != 0)
        {
            cout << "Overflow error" << endl;
            break;
        }
    }

    print_masqueue_status(mq);

    for (int i = 0; i < 10; i++)
    {
        my_type tmp = pop_task(&mq);
        if (tmp == -1.0)
        {
            cout << "Queue is empty" << endl;
            break;
        }
        cout << tmp << endl;
    }

    print_masqueue_status(mq);

    return 0;
}
