#include "defines.h"
#include "masqueue.h"
#include "listqueue.h"

#include <iostream>
#include <ctime>

#define EPS 10

using namespace std;

double get_time(int t1, int t2)
{
    double t = (double)(rand() % EPS) / EPS;
    return (double)((t2 - t1) * t + t1);
}

task gen_task()
{
    return (double)(rand() % EPS) / EPS;
}

int main()
{
    cout << "Hi!" << endl;
    srand(time(0));

    masqueue *mq1 = create_masqueue(100);
    masqueue *mq2 = create_masqueue(100);
    int flag = -1;
    int task1_in = 0;
    int task2_in = 0;
    int task1_out = 0;
    int task2_out = 0;
    int in_flag = 0;
    double model_time_in = 0;
    double model_time_out = 0;
    double afk_time = 0;

    while (task1_out != 100)
    {
        if (model_time_in <= model_time_out)
        {
            in_flag = rand() % 2;
            if (in_flag == 0) //first type
            {
                double tmp = get_time(1, 5);
                model_time_in += tmp;
                if (flag == -1)
                {
                    flag = 1;
                }
                if (add_task(mq1, gen_task()) != 0)
                    cout << "OVERFLOW ERROR" << endl;
                if (model_time_in > model_time_out && task1_in == task1_out && task2_in == task2_out)
                {
                    afk_time +=  model_time_in - model_time_out;
                    model_time_out = model_time_in;
                }
                task1_in++;
                //printf("%.1f A1 - %.1f (1-5)\n", model_time_in, tmp);
            }
            else //second type
            {
                double tmp = get_time(0, 3);
                model_time_in += tmp;
                if (flag == -1)
                {
                    flag = 2;
                }
                if (add_task(mq2, gen_task()) != 0)
                    cout << "OVERFLOW ERROR" << endl;
                if (model_time_in > model_time_out && task1_in == task1_out && task2_in == task2_out)
                {
                    afk_time +=  model_time_in - model_time_out;
                    model_time_out = model_time_in;
                }
                task2_in++;
                //printf("%.1f A2 - %.1f (0-3)\n", model_time_in, tmp);
            }
        }

        if (model_time_out <= model_time_in)
        {
            switch (flag)
            {
                case 1:
                {
                    if (model_time_in > model_time_out && task1_in == task1_out + 1)
                    {
                        afk_time +=  model_time_in - model_time_out;
                        model_time_out = model_time_in;
                    }
                    if (pop_task(mq1) != -1.0)
                    {
                        double tmp = get_time(0, 4);
                        model_time_out += tmp;
                        task1_out++;
                        //printf("%.1f P1 - %.1f (0-4)\n", model_time_out, tmp);
                        if (task1_out == task1_in && model_time_in <= model_time_out)
                            flag = -1;
                    }
                    else
                    {
                        if (pop_task(mq2) != -1.0)
                        {
                            double tmp = get_time(0, 1);
                            model_time_out += tmp;
                            task2_out++;
                            //printf("%.1f P2 - %.1f (0-1)\n", model_time_out, tmp);
                            flag = 2;
                            if (task2_out == task2_in && model_time_in <= model_time_out)
                                flag = -1;
                        }
                        else
                        {
                            model_time_out = model_time_in;
                        }
                    }
                    break;
                }
                case 2:
                {
                    if (model_time_in > model_time_out && task2_in == task2_out + 1)
                    {
                        afk_time +=  model_time_in - model_time_out;
                        model_time_out = model_time_in;
                    }
                    if (pop_task(mq2) != -1.0)
                    {
                        double tmp = get_time(0, 1);
                        model_time_out += tmp;
                        task2_out++;
                        //printf("%.1f P2 - %.1f (0-1)\n", model_time_out, tmp);
                        if (task2_out == task2_in && model_time_in <= model_time_out)
                            flag = -1;
                    }
                    else
                    {
                        if (pop_task(mq1) != -1.0)
                        {
                            double tmp = get_time(0, 4);
                            model_time_out += tmp;
                            task1_out++;
                            //printf("%.1f P1 - %.1f (0-4)\n", model_time_out, tmp);
                            flag = 1;
                            if (task1_out == task1_in && model_time_in <= model_time_out)
                                flag = -1;
                        }
                        else
                        {
                            model_time_out = model_time_in;
                        }
                    }
                    break;
                }
                default:
                {
                    cout << "FLAG ERROR: " << flag << endl;
                    break;
                }
            }
        }
    }

    /*print_masqueue_status(mq1);
    print_masqueue(mq1);

    print_masqueue_status(mq2);
    print_masqueue(mq2);*/

    cout << endl;
    //cout << "Model_Time_in: " << model_time_in << endl;
    cout << "Model_Time: " << model_time_out << endl;
    cout << "AFK time: " << afk_time << endl;

    if (model_time_out < model_time_in)
    {
        if (in_flag)
            cout << "Task1_in: " << task1_in << endl;
        else
            cout << "Task1_in: " << task1_in - 1 << endl;
        cout << "Task1_out: " << task1_out << endl;
        if (in_flag)
            cout << "Task2_in: " << task2_in - 1 << endl;
        else
            cout << "Task2_in: " << task2_in << endl;
        cout << "Task2_out: " << task2_out << endl;
    }
    else
    {
        cout << "Task1_in: " << task1_in << endl;
        cout << "Task1_out: " << task1_out << endl;
        cout << "Task2_in: " << task2_in << endl;
        cout << "Task2_out: " << task2_out << endl;
    }

    free_masqueue(mq1);
    free_masqueue(mq2);


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
