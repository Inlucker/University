#include "car_list_funcs.h"
#include "sorts.h"
#include "comporators.h"

/*void print_new_car_list(new_car *new_cars_list, int size_of_list)
{
    for (int i = 0; i < size_of_list; i++)
    {
        cout << new_cars_list[i].guarantee << endl;
    }
    cout << endl;
};

int add_record_to_new_car(int size_of_list, new_car **new_cars_list, new_car new_car_record)
{
    new_car *new_cars_list_new = new new_car [size_of_list + 1];
    memcpy(new_cars_list_new, *new_cars_list, sizeof(new_car) * size_of_list);
    new_cars_list_new[size_of_list] = new_car_record;
    //print_new_car_list(new_cars_list_new, size_of_list + 1);


    *new_cars_list = new new_car[size_of_list + 1];
    memcpy(*new_cars_list, new_cars_list_new, sizeof(new_car) * (size_of_list + 1));
    //print_new_car_list(*new_cars_list, size_of_list + 1);

    delete [] new_cars_list_new;

    return size_of_list + 1;
}*/

int main()
{
    cout << "Hi" << endl;

    int size_of_list = 0;
    //int *key_list = new int[size_of_list];
    car *cars_list = new car [size_of_list];

    string input_file_name = "car_list.txt";
    if (read_file(input_file_name, &cars_list, &size_of_list) != 0)
        return ERROR;

    cout << size_of_list << endl;

    /*string inp = "";
    car car_record;
    inp = "bValve; Russia; 3 000 000; black; new; 2022;";
    read_record(inp, &cars_list[0]);*/

    /*inp = "Steam; America; 2 000 000; white; old; 2022; 44000; 44; 22;";
    read_record(inp, &cars_list[1]);
    inp = "Valve2; Russia; 1 000 000; black; new; 2022;";
    read_record(inp, &cars_list[2]);
    print_car_list(cars_list, size_of_list);*/

    /*inp = "aSteam; America; 2 000 000; white; old; 2024; 44000; 44; 22;";
    read_record(inp, &car_record);

    //print_car_list(cars_list, size_of_list);

    size_of_list = add_record(&cars_list, size_of_list, car_record);

    print_car_list(cars_list, size_of_list);

    cout << size_of_list << endl;*/

    //size_of_list = delete_record(&cars_list, size_of_list, 1);
    /*if (print_car_record_by_pole(OWNERS_COUNT, "22", &cars_list, size_of_list) != -1) //Error when "Steam"
        cout << size_of_list << endl;
    if (size_of_list != -1)
    {
        print_car_list(cars_list, size_of_list);
    }

    int test1[10] = {1, 2, 3, 4, 5, 0, 7, 8, 9, 10};
    string test2[10] = {"Steam", "America", "2000000", "white", "old", "2022", "2024", "44000", "44", "22"};

    print_car_record_by_poles(test1, test2, &cars_list, size_of_list);*/

    car_sort_puz(&cars_list, size_of_list, (int(*)(const car*, const car*))comp_car_price);

    print_car_list(cars_list, size_of_list);

    delete [] cars_list;
    cout << "OK" << endl;

    /*string lol = "1234567890";
    //cin >> lol;
    int rez;
    int re = string_to_int(lol, &rez);
    cout << lol << " " << rez << " " << re << endl;*/

    //size_of_list = 5;
    /*int size_of_list = 5;
    new_car *new_cars_list = new new_car [size_of_list];

    //print_new_car_list(new_cars_list, size_of_list);

    for (int i = 0; i < size_of_list; i++)
    {
        new_cars_list[i].guarantee = 2022+i;
    }

    print_new_car_list(new_cars_list, size_of_list);

    new_car new_car_record;
    new_car_record.guarantee = 1000;
    size_of_list = add_record_to_new_car(size_of_list, &new_cars_list, new_car_record);
    print_new_car_list(new_cars_list, size_of_list);
    cout << size_of_list << endl;

    delete [] new_cars_list;
    cout << "OK" << endl;*/

    return 0;
}
