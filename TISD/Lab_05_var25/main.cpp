#include "defines.h"
#include "masqueue.h"
#include "listqueue.h"

#include <iostream>
#include <ctime>

using namespace std;

int main()
{
    cout << "Hello World!" << endl;
    srand(time(0));

    //cout << rand() % 5 + 1 << endl; // 1-5

    /*if (rand() % 2 == 0) //first type
    {

    }*/


    masqueue *mq = create_masqueue(10);
    if (mq == NULL)
    {
        cout << "Create_masqueue ERROR" << endl;;
        return CREATE_ERROR;
    }

    for (int i = 0; i < 10; i++)
    {
        if (add_task(mq, (task)i) != 0)
        {
            cout << "Overflow error" << endl;
            break;
        }
    }

    print_masqueue_status(mq);
    print_masqueue(mq);

    for (int i = 0; i < 8; i++)
    {
        task tmp = pop_task(mq);
        if (tmp == -1.0)
        {
            cout << "Queue is empty" << endl;
            break;
        }
        //cout << tmp << endl;
    }

    if (add_task(mq, 1.2) != 0)
    {
        cout << "Overflow error" << endl;
    }

    print_masqueue_status(mq);
    print_masqueue(mq);

    free(mq);

    cout << "\nLISTQUEUE:" << endl;

    listqueue *lq = create_listqueue();
    if (lq == NULL)
    {
        cout << "Create_listqueue ERROR" << endl;;
        return CREATE_ERROR;
    }

    for (int i = 0; i < 10; i++)
    {
        add_task(lq, (task)i);
    }

    print_listqueue(lq);

    free(lq);

    return 0;
}
