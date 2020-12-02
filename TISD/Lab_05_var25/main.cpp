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

    int input = -1;

    //cout << sizeof (car) << " " << sizeof (price_keys) << endl;

    while (input != 0)
    {
        cout << endl;
        cout << "Mas_stack commands:" << endl;
        cout << " 1 - Model mas_queue" << endl;
        cout << " 2 - Model list_queue" << endl;
        cout << " 3 - Compare time" << endl;
        cout << " 4 - Compare memory" << endl;

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
            printf("Mas_model_time: %.4f seconds\n\n", seconds);
        }
        case 2:
        {
            clock_t start = clock();
            list_model();
            clock_t end = clock();
            double seconds = (double)(end - start) / CLOCKS_PER_SEC;
            printf("List_model_time: %.4f seconds\n\n", seconds);
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
