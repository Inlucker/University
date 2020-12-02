#include "defines.h"
#include "masqueue.h"
#include "listqueue.h"
#include "modelation.h"

#include <iostream>
#include <ctime>

#define ITERATIONS 1e8//100000000

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

    int input = -1;

    //cout << sizeof (car) << " " << sizeof (price_keys) << endl;

    while (input != 0)
    {
        cout << endl;
        cout << "Mas_stack commands:" << endl;
        cout << "1 - Model mas_queue" << endl;
        cout << "2 - Model list_queue" << endl;
        cout << "3 - Compare time" << endl;
        cout << "4 - Compare memory" << endl;
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
            clock_t start = clock();
            mas_model();
            clock_t end = clock();
            double seconds = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Mas_model_time: %.3f seconds\n\n", seconds);
            break;
        }
        case 2:
        {
            clock_t start = clock();
            list_model();
            clock_t end = clock();
            double seconds = (double)(end - start) / CLOCKS_PER_SEC;
            printf("List_model_time: %.3f seconds\n\n", seconds);
            break;
        }
        case 3:
        {
            /*_flushall();
            cout << "Enter the size for mas_queue: ";
            int size;
            cin >> size;*/
            cout << "Iteartions number: " << ITERATIONS << endl;
            masqueue *mq = create_masqueue(ITERATIONS);
            clock_t start = clock();
            for (int i = 0; i < ITERATIONS; i++)
            {
                if (add_task(mq, gen_task()) != 0)
                {
                    cout << "OVERFLOW ERROR in mas_queue" << endl;
                    break;
                }
            }
            clock_t end = clock();
            double seconds = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Add_time for mas_queue: %.3f seconds\n", seconds);

            start = clock();
            for (int i = 0; i < ITERATIONS; i++)
            {
                if (pop_task(mq) == -1.0)
                {
                    cout << "EMPTY ERROR in mas_queue" << endl;
                    break;
                }
            }
            end = clock();
            seconds = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Pop_time for mas_queue: %.3f seconds\n", seconds);

            start = clock();
            free_masqueue(mq);
            end = clock();
            seconds = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Free_time for mas_queue: %.3f seconds\n", seconds);

            masqueue *lq = create_masqueue(ITERATIONS);
            start = clock();
            for (int i = 0; i < ITERATIONS; i++)
            {
                add_task(lq, gen_task());
            }
            end = clock();
            seconds = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Add_time for list_queue: %.3f seconds\n", seconds);

            start = clock();
            for (int i = 0; i < ITERATIONS; i++)
            {
                if (pop_task(lq) == -1.0)
                {
                    cout << "EMPTY ERROR in mas_queue" << endl;
                    break;
                }
            }
            end = clock();
            seconds = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Pop_time for list_queue: %.3f seconds\n", seconds);

            start = clock();
            free_masqueue(lq);
            end = clock();
            seconds = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Free_time for list_queue: %.3f seconds\n", seconds);
            break;
        }
        case 4:
        {
            _flushall();
            cout << "Input size: ";
            int elems = 1;
            cin >> elems;
            cout << "Mas_stack: " << elems * sizeof(task) + sizeof (masqueue) << " bytes." << endl;
            cout << "List_stack: " << (elems + 1) * sizeof(listqueue_element) + sizeof (listqueue)  << " bytes." << endl;
            break;
        }
        case 0:
        {
            cout << "Good buy!" << endl;
            break;
        }
        default:
            cout << "Wrong command" << endl;
            break;
        }
    }

    return 0;
}
