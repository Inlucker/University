#include <iostream>
#include <cstring>
//#include "structs.h"

#define ERROR -1;

using namespace std;

struct new_car
{
    int guarantee;
};

struct old_car
{
    int year_of_release;
    int probeg;
    int repair_count;
    int owners_count;
};

struct state
{
    bool is_new;
    new_car new_car_params;
    old_car old_car_params;
};

struct car
{
    string brand;
    string manufacturer_country;
    int price;
    string color;
    state condition;
};

int string_to_int(string input, int *rez)
{
    int tmp = 0;
    int mnojitel = 1;
    for (int i = input.length() - 1; i >= 0; i--)
    {
        if (input[i] >= '0' && input[i] <= '9')
        {
            tmp += (input[i] - '0') * mnojitel;
            mnojitel *= 10;
        }
        else if (input[i] != ' ')
        {
            *rez = ERROR;
            return ERROR;
        }
    }
    *rez = tmp;
    return 0;
}

int read_record (string input, car *car_record_rez)
{
    int i = 0;
    car car_record;
    int j = 0;
    while (j < input.length())
    {
        string tmp = "";
        while (input[j] != ';')
        {
            if (input[j] != ' ')
                tmp += input[j];
            j++;
        }
        j++;

        switch (i)
        {
        case 0:
            car_record.brand = tmp;
            break;
        case 1:
            car_record.manufacturer_country = tmp;
            break;
        case 2:
            if (string_to_int(tmp, &car_record.price))
            {
                return ERROR;
            }
            break;
        case 3:
            car_record.color = tmp;
            break;
        case 4:
            if (tmp == "new")
                car_record.condition.is_new = true;
            else if (tmp == "old")
                car_record.condition.is_new = false;
            break;
        case 5:
            if (car_record.condition.is_new)
            {
                if (string_to_int(tmp, &car_record.condition.new_car_params.guarantee))
                    return ERROR;
            }
            else
                if (string_to_int(tmp, &car_record.condition.old_car_params.year_of_release))
                    return ERROR;
            break;
        case 6:
            if (car_record.condition.is_new)
            {
                return ERROR;
            }
            else
                if (string_to_int(tmp, &car_record.condition.old_car_params.probeg))
                    return ERROR;
            break;
        case 7:
            if (car_record.condition.is_new)
            {
                return ERROR;
            }
            else
                if (string_to_int(tmp, &car_record.condition.old_car_params.repair_count))
                    return ERROR;
            break;
        case 8:
            if (car_record.condition.is_new)
            {
                return ERROR;
            }
            else
                if (string_to_int(tmp, &car_record.condition.old_car_params.owners_count))
                    return ERROR;
            break;
        default:
            return ERROR;
        }

        i++;
    }
    *car_record_rez = car_record;
    return 0;
}

void print_car_list(car *cars_list, int size_of_list)
{
    for (int i = 0; i < size_of_list; i++)
    {
        cout << cars_list[i].brand << "; " << cars_list[i].manufacturer_country << "; " << cars_list[i].price << "; " << cars_list[i].color << "; " << cars_list[i].condition.is_new << "; ";
        if (cars_list[i].condition.is_new)
            cout << cars_list[i].condition.new_car_params.guarantee << ";" << endl;
        else
            cout << cars_list[i].condition.old_car_params.year_of_release << "; " << cars_list[i].condition.old_car_params.probeg << "; "
                 << cars_list[i].condition.old_car_params.repair_count << "; " << cars_list[i].condition.old_car_params.owners_count << ";" << endl;
    }
    cout << endl;
}

void car_list_copy (car *car_list1, car *car_list2, int size_of_list)
{
    for (int i = 0; i < size_of_list; i++)
    {
        car_list1[i] = car_list2[i];
    }
}

int add_record (car **car_list, int size_of_list, car car_record)
{
    car *cars_list_new = new car [size_of_list + 1];
    car_list_copy(cars_list_new, *car_list, size_of_list);
    cars_list_new[size_of_list] = car_record;
    /*cout << "cars_list_new:" << endl;
    print_car_list(cars_list_new, size_of_list + 1);*/

    delete[] *car_list;
    *car_list = new car[size_of_list + 1];
    car_list_copy(*car_list, cars_list_new, size_of_list + 1);
    /*cout << "*car_list:" << endl;
    print_car_list(*car_list, size_of_list + 1);*/

    delete [] cars_list_new;

    return size_of_list + 1;
}

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

    int size_of_list = 1;
    car *cars_list = new car [size_of_list];

    string inp = "";
    car car_record;
    inp = "Valve; Russia; 1 000 000; black; new; 2022;";
    cout << read_record(inp, &cars_list[0]) << endl;
    print_car_list(cars_list, size_of_list);

    inp = "Steam; America; 2 000 000; white; old; 2022; 44000; 44; 22;";
    cout << read_record(inp, &car_record) << endl;

    print_car_list(cars_list, size_of_list);

    size_of_list = add_record(&cars_list, size_of_list, car_record);

    print_car_list(cars_list, size_of_list);

    cout << size_of_list << endl;

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
