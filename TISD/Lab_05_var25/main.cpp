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

uint64_t tick(void)
{
    uint32_t high, low;
    __asm__ __volatile__(
        "rdtsc\n"
        "movl %%edx, %0\n"
        "movl %%eax, %1\n"
        : "=r"(high), "=r"(low)::"%rax", "%rbx", "%rcx", "%rdx");

    uint64_t ticks = ((uint64_t)high << 32) | low;

    return ticks;
}

int main()
{
    cout << "Hi!" << endl;
    srand(time(0));

    model();
    //mas_model3();
    //avg_model();

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
        cout << "5 - Fragmentation check" << endl;
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
            mas_model2();
            clock_t end = clock();
            double seconds = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Mas_model_time: %.3f seconds\n\n", seconds);
            break;
        }
        case 2:
        {
            clock_t start = clock();
            list_model2();
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

            listqueue *lq = create_listqueue();
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
                    cout << "EMPTY ERROR in list_queue" << endl;
                    break;
                }
            }
            end = clock();
            seconds = (double)(end - start) / CLOCKS_PER_SEC;
            printf("Pop_time for list_queue: %.3f seconds\n", seconds);

            for (int i = 0; i < ITERATIONS; i++)
            {
                add_task(lq, gen_task());
            }
            start = clock();
            free_listqueue(lq);
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
        case 5:
        {
            listqueue *lq = create_listqueue();
            for (int i = 0; i < 10; i++)
            {
                add_task(lq, gen_task());
            }

            cout << "Start listque: " << endl;
            print_listqueue(lq);

            listqueue_element *free_memory_list[10];
            //int free_memory_list_id = 0;

            for (int i = 0; i < 10; i++)
            {
                free_memory_list[i] = lq->ptr_out;
                pop_task(lq);
            }

            for (int i = 0; i < 10; i++)
            {
                add_task(lq, gen_task());
            }

            cout << "New listqueue: " << endl;
            print_listqueue(lq);

            cout << "Free memory list: " << endl;
            for (int i = 0; i < 10; i++)
            {
                cout << "Ptr" << i << " = " << free_memory_list[i] << endl;
            }
            cout << endl;

            cout << "Equal Ptrs: (Free list and New listqueue)" << endl;
            listqueue_element *iterator = lq->ptr_out;
            for (int i = 0; i < 10; i++)
            {
                for (int j = 0; j < 10; j++)
                {
                    if (free_memory_list[j] == iterator)
                    cout << "Ptr" << j << " = " << free_memory_list[j] << " and Ptr" << i << " = " << iterator << endl;
                }
                iterator = iterator->next_ptr;
            }
            free_listqueue(lq);
            break;
        }
        /*case 6:
        {
            cout << "Iteartions number: " << ITERATIONS << endl;
            masqueue *mq = create_masqueue(ITERATIONS);
            uint64_t start, end;

            start = tick();
            for (int i = 0; i < ITERATIONS; i++)
            {
                if (add_task(mq, gen_task()) != 0)
                {
                    cout << "OVERFLOW ERROR in mas_queue" << endl;
                    break;
                }
            }
            end = tick();
            printf("%s %ju\n",
                   "Add_time for mas_queue:", end - start);
            //printf("Add_time for mas_queue: %.3f seconds\n", seconds);

            start = tick();
            for (int i = 0; i < ITERATIONS; i++)
            {
                if (pop_task(mq) == -1.0)
                {
                    cout << "EMPTY ERROR in mas_queue" << endl;
                    break;
                }
            }
            end = tick();
            printf("%s %ju\n",
                   "Pop_time for mas_queue:", end - start);

            start = tick();
            free_masqueue(mq);
            end = tick();
            printf("%s %ju\n",
                   "Free_time for mas_queue:", end - start);

            listqueue *lq = create_listqueue();

            start = tick();
            for (int i = 0; i < ITERATIONS; i++)
            {
                add_task(lq, gen_task());
            }
            end = tick();
            printf("%s %ju\n",
                   "Add_time for list_queue:", end - start);
            //printf("Add_time for mas_queue: %.3f seconds\n", seconds);

            start = tick();
            for (int i = 0; i < ITERATIONS; i++)
            {
                if (pop_task(lq) == -1.0)
                {
                    cout << "EMPTY ERROR in list_queue" << endl;
                    break;
                }
            }
            end = tick();
            printf("%s %ju\n",
                   "Pop_time for list_queue:", end - start);

            for (int i = 0; i < ITERATIONS; i++)
            {
                add_task(lq, gen_task());
            }
            start = tick();
            free_listqueue(lq);
            end = tick();
            printf("%s %ju\n",
                   "Free_time for list_queue:", end - start);
            break;
        }*/
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
