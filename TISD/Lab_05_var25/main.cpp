#include "defines.h"
#include "masqueue.h"
#include "listqueue.h"
#include "modelation.h"

#include <iostream>
#include <ctime>

using namespace std;

/*double get_time(int t1, int t2)
{
    double t = (double)(rand() % EPS) / EPS;
    return (double)((t2 - t1) * t + t1);
}

task gen_task()
{
    return (double)(rand() % EPS) / EPS;
}*/

int main()
{
    cout << "Hi!" << endl;
    srand(time(0));

    clock_t start = clock();
    mas_model();
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Mas_model_time: %.4f seconds\n", seconds);

    /*cout << "MASQUEUE:" << endl;

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

    free_masqueue(mq);

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

    free_listqueue(lq);*/

    return 0;
}
