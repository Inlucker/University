#include <random>
#include <iostream>
#include "modelation.h"
#include "masqueue.h"
#include "listqueue.h"

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

void mas_model()
{
    masqueue *mq1 = create_masqueue(100);
    masqueue *mq2 = create_masqueue(100);
    int flag = -1;
    int task1_in = 0;
    int task2_in = 0;
    int task1_out = 0;
    int task2_out = 0;
    double average_queue1_length = 0;
    double average_queue2_length = 0;
    int in_flag = 0;
    double model_time_in = 0;
    double model_time_out = 0;
    double afk_time = 0;

    while (task1_out != 1000)
    {
        if (model_time_in <= model_time_out)
        {
            in_flag = rand() % 2;
            if (in_flag == 0) //first type
            {
                double tmp = get_time(1, 5);
                average_queue1_length = ((average_queue1_length) * (model_time_in / (model_time_in + tmp))) + ((task1_in + 1 - task1_out) * (tmp / (model_time_in + tmp)));
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
                average_queue2_length = ((average_queue2_length) * (model_time_in / (model_time_in + tmp))) + ((task2_in + 1 - task2_out) * (tmp / (model_time_in + tmp)));
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
                        average_queue1_length = ((average_queue1_length) * (model_time_out / (model_time_out + tmp))) + ((task1_in - task1_out - 1) * (tmp / (model_time_out + tmp)));
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
                            average_queue2_length = ((average_queue2_length) * (model_time_out / (model_time_out + tmp))) + ((task2_in - task2_out - 1) * (tmp / (model_time_out + tmp)));
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

                    if (task1_out % 100 == 0)
                    {
                        cout << "Info for " << task1_out << " task1_out: " << endl;
                        cout << "Current queue1 length: " << task1_in - task1_out << endl;
                        cout << "Average queue1 length: " << average_queue1_length << endl;
                        cout << "Current queue2 length: " << task2_in - task2_out << endl;
                        cout << "Average queue2 length: " << average_queue2_length<< endl;
                        cout << endl;
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
                        average_queue2_length = ((average_queue2_length) * (model_time_out / (model_time_out + tmp))) + ((task2_in - task2_out - 1) * (tmp / (model_time_out + tmp)));
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
                            average_queue1_length = ((average_queue1_length) * (model_time_out / (model_time_out + tmp))) + ((task1_in - task1_out - 1) * (tmp / (model_time_out + tmp)));
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

    //cout << "Model_Time_in: " << model_time_in << endl;
    cout << "Model Time: " << model_time_out << endl;
    cout << "AFK time: " << afk_time << endl;
    cout << "Work time: " << model_time_out - afk_time << endl;

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

    cout << "OA_Procs: " << task2_out + task1_out << endl;

    free_masqueue(mq1);
    free_masqueue(mq2);
    cout << endl;
}

void list_model()
{
    listqueue *lq1 = create_listqueue();
    listqueue *lq2 = create_listqueue();
    int flag = -1;
    int task1_in = 0;
    int task2_in = 0;
    int task1_out = 0;
    int task2_out = 0;
    double average_queue1_length = 0;
    double average_queue2_length = 0;
    int in_flag = 0;
    double model_time_in = 0;
    double model_time_out = 0;
    double afk_time = 0;

    while (task1_out != 1000)
    {
        if (model_time_in <= model_time_out)
        {
            in_flag = rand() % 2;
            if (in_flag == 0) //first type
            {
                double tmp = get_time(1, 5);
                average_queue1_length = ((average_queue1_length) * (model_time_in / (model_time_in + tmp))) + ((task1_in + 1 - task1_out) * (tmp / (model_time_in + tmp)));
                model_time_in += tmp;
                if (flag == -1)
                {
                    flag = 1;
                }
                add_task(lq1, gen_task());
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
                average_queue2_length = ((average_queue2_length) * (model_time_in / (model_time_in + tmp))) + ((task2_in + 1 - task2_out) * (tmp / (model_time_in + tmp)));
                model_time_in += tmp;
                if (flag == -1)
                {
                    flag = 2;
                }
                add_task(lq2, gen_task());
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
                    if (pop_task(lq1) != -1.0)
                    {
                        double tmp = get_time(0, 4);
                        average_queue1_length = ((average_queue1_length) * (model_time_out / (model_time_out + tmp))) + ((task1_in - task1_out - 1) * (tmp / (model_time_out + tmp)));
                        model_time_out += tmp;
                        task1_out++;
                        //printf("%.1f P1 - %.1f (0-4)\n", model_time_out, tmp);
                        if (task1_out == task1_in && model_time_in <= model_time_out)
                            flag = -1;
                    }
                    else
                    {
                        if (pop_task(lq2) != -1.0)
                        {
                            double tmp = get_time(0, 1);
                            average_queue2_length = ((average_queue2_length) * (model_time_out / (model_time_out + tmp))) + ((task2_in - task2_out - 1) * (tmp / (model_time_out + tmp)));
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

                    if (task1_out % 100 == 0)
                    {
                        cout << "Info for " << task1_out << " task1_out: " << endl;
                        cout << "Current queue1 length: " << task1_in - task1_out << endl;
                        cout << "Average queue1 length: " << average_queue1_length << endl;
                        cout << "Current queue2 length: " << task2_in - task2_out << endl;
                        cout << "Average queue2 length: " << average_queue2_length<< endl;
                        cout << endl;
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
                    if (pop_task(lq2) != -1.0)
                    {
                        double tmp = get_time(0, 1);
                        average_queue2_length = ((average_queue2_length) * (model_time_out / (model_time_out + tmp))) + ((task2_in - task2_out - 1) * (tmp / (model_time_out + tmp)));
                        model_time_out += tmp;
                        task2_out++;
                        //printf("%.1f P2 - %.1f (0-1)\n", model_time_out, tmp);
                        if (task2_out == task2_in && model_time_in <= model_time_out)
                            flag = -1;
                    }
                    else
                    {
                        if (pop_task(lq1) != -1.0)
                        {
                            double tmp = get_time(0, 4);
                            average_queue1_length = ((average_queue1_length) * (model_time_out / (model_time_out + tmp))) + ((task1_in - task1_out - 1) * (tmp / (model_time_out + tmp)));
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

    //cout << "Model_Time_in: " << model_time_in << endl;
    cout << "Model Time: " << model_time_out << endl;
    cout << "AFK time: " << afk_time << endl;
    cout << "Work time: " << model_time_out - afk_time << endl;

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

    cout << "OA_Procs: " << task2_out + task1_out << endl;

    free_listqueue(lq1);
    free_listqueue(lq2);
    cout << endl;
}
