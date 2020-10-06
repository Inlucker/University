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
    car *cars_list = new car [size_of_list];

    string input_file_name = "car_list.txt";
    if (read_file(input_file_name, &cars_list, &size_of_list) != 0)
        return ERROR;
    int *key_list = new int [size_of_list];

    for (int i = 0; i < size_of_list; i++)
        key_list[i] = i;

    cout << size_of_list << endl;

    //car_sort_puz(&cars_list, size_of_list, (int(*)(const car*, const car*))comp_car_price);
    //car_sort_qsort(&cars_list, size_of_list, (int(*)(const car*, const car*))comp_car_price);
    car_sort_puz_by_keys(&cars_list, size_of_list, (int(*)(const car*, const car*))comp_car_brand, &key_list);

    print_key_list(key_list, size_of_list);
    print_car_list_by_keys(cars_list, size_of_list, key_list);

    car_sort_puz(&cars_list, size_of_list, (int(*)(const car*, const car*))comp_car_brand);

    print_car_list(cars_list, size_of_list);

    delete [] cars_list;
    cout << "OK" << endl;

    return 0;
}
