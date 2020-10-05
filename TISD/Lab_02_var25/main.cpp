#include <iostream>
#include <cstring>
//#include "structs.h"

#define ERROR -1;
/*#define BRAND 0;
#define MANUFACURER_COUNTRY 1;
#define PRICE 2;
#define COLOR 3;
#define IS_NEW 4;
#define GUARANTEE 5;
#define YEAR_OF_RELEASE 6;
#define PROBEG 7;
#define REPAIR_COUNT 8;
#define OWNERS_COUNT 9;*/

using namespace std;

enum
{
    BRAND = 0,
    MANUFACURER_COUNTRY = 1,
    PRICE = 2,
    COLOR = 3,
    IS_NEW = 4,
    GUARANTEE = 5,
    YEAR_OF_RELEASE = 6,
    PROBEG = 7,
    REPAIR_COUNT = 8,
    OWNERS_COUNT = 9
};

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

union state
{
    new_car new_car_params;
    old_car old_car_params;
};

struct car
{
    string brand;
    string manufacturer_country;
    int price;
    string color;
    bool is_new;
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
                car_record.is_new = true;
            else if (tmp == "old")
                car_record.is_new = false;
            break;
        case 5:
            if (car_record.is_new)
            {
                if (string_to_int(tmp, &car_record.condition.new_car_params.guarantee))
                    return ERROR;
            }
            else
                if (string_to_int(tmp, &car_record.condition.old_car_params.year_of_release))
                    return ERROR;
            break;
        case 6:
            if (car_record.is_new)
            {
                return ERROR;
            }
            else
                if (string_to_int(tmp, &car_record.condition.old_car_params.probeg))
                    return ERROR;
            break;
        case 7:
            if (car_record.is_new)
            {
                return ERROR;
            }
            else
                if (string_to_int(tmp, &car_record.condition.old_car_params.repair_count))
                    return ERROR;
            break;
        case 8:
            if (car_record.is_new)
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

void print_car_record(car car_record)
{
    cout << car_record.brand << "; " << car_record.manufacturer_country << "; " << car_record.price << "; " << car_record.color << "; ";// << car_record.is_new << "; ";
    if (car_record.is_new)
        cout << "new; " << car_record.condition.new_car_params.guarantee << ";" << endl;
    else
        cout << "old; " << car_record.condition.old_car_params.year_of_release << "; " << car_record.condition.old_car_params.probeg << "; "
             << car_record.condition.old_car_params.repair_count << "; " << car_record.condition.old_car_params.owners_count << ";" << endl;
}

void print_car_list(car *cars_list, int size_of_list)
{
    for (int i = 0; i < size_of_list; i++)
    {
        //cout << i << " ";
        /*cout << cars_list[i].brand << "; " << cars_list[i].manufacturer_country << "; " << cars_list[i].price << "; " << cars_list[i].color << "; " << cars_list[i].is_new << "; ";
        if (cars_list[i].is_new)
            cout << cars_list[i].condition.new_car_params.guarantee << ";" << endl;
        else
            cout << cars_list[i].condition.old_car_params.year_of_release << "; " << cars_list[i].condition.old_car_params.probeg << "; "
                 << cars_list[i].condition.old_car_params.repair_count << "; " << cars_list[i].condition.old_car_params.owners_count << ";" << endl;*/
        print_car_record(cars_list[i]);
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

void car_record_copy (car *car_list1, car *car_list2, int i)
{
    car_list1[i] = car_list2[i+1];
}

int delete_record (car **car_list, int size_of_list, int id)
{
    if (id > size_of_list && id <= 0)
        return -1;
    car *cars_list_new = new car [size_of_list - 1];
    car_list_copy(cars_list_new, *car_list, id - 1);
    for (int i = id - 1; i < size_of_list - 1; i++)
        car_record_copy(cars_list_new, *car_list, i);
    //cout << car_list[0]->brand << endl;
    //print_car_list(cars_list_new, size_of_list - 1);

    delete[] *car_list;
    *car_list = new car[size_of_list - 1];
    car_list_copy(*car_list, cars_list_new, size_of_list - 1);
    /*cout << "*car_list:" << endl;
    print_car_list(*car_list, size_of_list - 1);*/

    delete [] cars_list_new;

    return size_of_list - 1;
}

int delete_car_record_by_pole(int pole, string znach, car **car_list, int *size_of_list)
{
    int tmp_size = *size_of_list;
    switch(pole)
    {
    case BRAND:
        for (int i = 0; i < tmp_size; i++)
            if (((*car_list)+i)->brand == znach)
            {
                tmp_size = delete_record(car_list, tmp_size, i + 1);
                i--;
            }
        break;
    case MANUFACURER_COUNTRY:
        for (int i = 0; i < tmp_size; i++)
            if (((*car_list)+i)->manufacturer_country == znach)
            {
                tmp_size = delete_record(car_list, tmp_size, i + 1);
                i--;
            }
        break;
    case PRICE:
        for (int i = 0; i < tmp_size; i++)
        {
            int tmp_znach = 0;
            if (string_to_int(znach, &tmp_znach) != 0)
                return ERROR;
            if (((*car_list)+i)->price == tmp_znach)
            {
                tmp_size = delete_record(car_list, tmp_size, i + 1);
                i--;
            }
        }
        break;
    case COLOR:
        for (int i = 0; i < tmp_size; i++)
            if (((*car_list)+i)->color == znach)
            {
                tmp_size = delete_record(car_list, tmp_size, i + 1);
                i--;
            }
        break;
    case IS_NEW:
        for (int i = 0; i < tmp_size; i++)
        {
            string tmp_znach = "";
            if (((*car_list)+i)->is_new)
                tmp_znach = "new";
            else
                tmp_znach = "old";
            if (tmp_znach == znach)
            {
                tmp_size = delete_record(car_list, tmp_size, i + 1);
                i--;
            }
        }
        break;
    case GUARANTEE:
        for (int i = 0; i < tmp_size; i++)
        {
            if (((*car_list)+i)->is_new)
            {
                int tmp_znach = 0;
                if (string_to_int(znach, &tmp_znach) != 0)
                    return ERROR;
                if (((*car_list)+i)->condition.new_car_params.guarantee == tmp_znach)
                {
                    tmp_size = delete_record(car_list, tmp_size, i + 1);
                    i--;
                }
            }
        }
        break;
    case YEAR_OF_RELEASE:
        for (int i = 0; i < tmp_size; i++)
        {
            if (!((*car_list)+i)->is_new)
            {
                int tmp_znach = 0;
                if (string_to_int(znach, &tmp_znach) != 0)
                    return ERROR;
                if (((*car_list)+i)->condition.old_car_params.year_of_release == tmp_znach)
                {
                    tmp_size = delete_record(car_list, tmp_size, i + 1);
                    i--;
                }
            }
        }
        break;
    case PROBEG:
        for (int i = 0; i < tmp_size; i++)
        {
            if (!((*car_list)+i)->is_new)
            {
                int tmp_znach = 0;
                if (string_to_int(znach, &tmp_znach) != 0)
                    return ERROR;
                if (((*car_list)+i)->condition.old_car_params.probeg == tmp_znach)
                {
                    tmp_size = delete_record(car_list, tmp_size, i + 1);
                    i--;
                }
            }
        }
        break;
    case REPAIR_COUNT:
        for (int i = 0; i < tmp_size; i++)
        {
            if (!((*car_list)+i)->is_new)
            {
                int tmp_znach = 0;
                if (string_to_int(znach, &tmp_znach) != 0)
                    return ERROR;
                if (((*car_list)+i)->condition.old_car_params.repair_count == tmp_znach)
                {
                    tmp_size = delete_record(car_list, tmp_size, i + 1);
                    i--;
                }
            }
        }
        break;
    case OWNERS_COUNT:
        for (int i = 0; i < tmp_size; i++)
        {
            if (!((*car_list)+i)->is_new)
            {
                int tmp_znach = 0;
                if (string_to_int(znach, &tmp_znach) != 0)
                    return ERROR;
                if (((*car_list)+i)->condition.old_car_params.owners_count == tmp_znach)
                {
                    tmp_size = delete_record(car_list, tmp_size, i + 1);
                    i--;
                }
            }
        }
        break;
    default:
        return ERROR;
        break;
    }
    *size_of_list = tmp_size;
    return 0;
}

int print_car_record_by_pole(int pole, string znach, car **car_list, int size_of_list)
{
    switch(pole)
    {
    case BRAND:
        for (int i = 0; i < size_of_list; i++)
            if (((*car_list)+i)->brand == znach)
                print_car_record(*((*car_list)+i));
        break;
    case MANUFACURER_COUNTRY:
        for (int i = 0; i < size_of_list; i++)
            if (((*car_list)+i)->manufacturer_country == znach)
                print_car_record(*((*car_list)+i));
        break;
    case PRICE:
        for (int i = 0; i < size_of_list; i++)
        {
            int tmp_znach = 0;
            if (string_to_int(znach, &tmp_znach) != 0)
                return ERROR;
            if (((*car_list)+i)->price == tmp_znach)
                print_car_record(*((*car_list)+i));
        }
        break;
    case COLOR:
        for (int i = 0; i < size_of_list; i++)
            if (((*car_list)+i)->color == znach)
                print_car_record(*((*car_list)+i));
        break;
    case IS_NEW:
        for (int i = 0; i < size_of_list; i++)
        {
            string tmp_znach = "";
            if (((*car_list)+i)->is_new)
                tmp_znach = "new";
            else
                tmp_znach = "old";
            if (tmp_znach == znach)
                print_car_record(*((*car_list)+i));
        }
        break;
    case GUARANTEE:
        for (int i = 0; i < size_of_list; i++)
        {
            if (((*car_list)+i)->is_new)
            {
                int tmp_znach = 0;
                if (string_to_int(znach, &tmp_znach) != 0)
                    return ERROR;
                if (((*car_list)+i)->condition.new_car_params.guarantee == tmp_znach)
                    print_car_record(*((*car_list)+i));
            }
        }
        break;
    case YEAR_OF_RELEASE:
        for (int i = 0; i < size_of_list; i++)
        {
            if (!((*car_list)+i)->is_new)
            {
                int tmp_znach = 0;
                if (string_to_int(znach, &tmp_znach) != 0)
                    return ERROR;
                if (((*car_list)+i)->condition.old_car_params.year_of_release == tmp_znach)
                    print_car_record(*((*car_list)+i));
            }
        }
        break;
    case PROBEG:
        for (int i = 0; i < size_of_list; i++)
        {
            if (!((*car_list)+i)->is_new)
            {
                int tmp_znach = 0;
                if (string_to_int(znach, &tmp_znach) != 0)
                    return ERROR;
                if (((*car_list)+i)->condition.old_car_params.probeg == tmp_znach)
                    print_car_record(*((*car_list)+i));
            }
        }
        break;
    case REPAIR_COUNT:
        for (int i = 0; i < size_of_list; i++)
        {
            if (!((*car_list)+i)->is_new)
            {
                int tmp_znach = 0;
                if (string_to_int(znach, &tmp_znach) != 0)
                    return ERROR;
                if (((*car_list)+i)->condition.old_car_params.repair_count == tmp_znach)
                    print_car_record(*((*car_list)+i));
            }
        }
        break;
    case OWNERS_COUNT:
        for (int i = 0; i < size_of_list; i++)
        {
            if (!((*car_list)+i)->is_new)
            {
                int tmp_znach = 0;
                if (string_to_int(znach, &tmp_znach) != 0)
                    return ERROR;
                if (((*car_list)+i)->condition.old_car_params.owners_count == tmp_znach)
                    print_car_record(*((*car_list)+i));
            }
        }
        break;
    default:
        return ERROR;
        break;
    }
    return 0;
}

int print_car_record_by_poles(int pole[10], string znach[10], car **car_list, int size_of_list)
{
    for (int i = 0; i < size_of_list; i++)
    {
        bool flag = true;

        for (int j = 0; j < 10; j++)
        {
            if (pole[j])
                switch(j)
                {
                case BRAND:
                    if (((*car_list)+i)->brand != znach[j])
                        flag = false;
                    break;
                case MANUFACURER_COUNTRY:
                    if (((*car_list)+i)->manufacturer_country != znach[j])
                        flag = false;
                    break;
                case PRICE:
                {
                    int tmp_znach = 0;
                    if (string_to_int(znach[j], &tmp_znach) != 0)
                        return ERROR;
                    if (((*car_list)+i)->price != tmp_znach)
                        flag = false;
                }
                    break;
                case COLOR:
                    if (((*car_list)+i)->color != znach[j])
                        flag = false;
                    break;
                case IS_NEW:
                {
                    string tmp_znach = "";
                    if (((*car_list)+i)->is_new)
                        tmp_znach = "new";
                    else
                        tmp_znach = "old";
                    if (tmp_znach != znach[j])
                        flag = false;
                }
                    break;
                case GUARANTEE:
                {
                    if (((*car_list)+i)->is_new)
                    {
                        int tmp_znach = 0;
                        if (string_to_int(znach[j], &tmp_znach) != 0)
                            return ERROR;
                        if (((*car_list)+i)->condition.new_car_params.guarantee != tmp_znach)
                            flag = false;
                    }
                }
                    break;
                case YEAR_OF_RELEASE:
                {
                    if (!((*car_list)+i)->is_new)
                    {
                        int tmp_znach = 0;
                        if (string_to_int(znach[j], &tmp_znach) != 0)
                            return ERROR;
                        if (((*car_list)+i)->condition.old_car_params.year_of_release != tmp_znach)
                            flag = false;
                    }
                }
                    break;
                case PROBEG:
                {
                    if (!((*car_list)+i)->is_new)
                    {
                        int tmp_znach = 0;
                        if (string_to_int(znach[j], &tmp_znach) != 0)
                            return ERROR;
                        if (((*car_list)+i)->condition.old_car_params.probeg != tmp_znach)
                            flag = false;
                    }
                }
                    break;
                case REPAIR_COUNT:
                {
                    if (!((*car_list)+i)->is_new)
                    {
                        int tmp_znach = 0;
                        if (string_to_int(znach[j], &tmp_znach) != 0)
                            return ERROR;
                        if (((*car_list)+i)->condition.old_car_params.repair_count != tmp_znach)
                            flag = false;
                    }
                }
                    break;
                case OWNERS_COUNT:
                {
                    if (!((*car_list)+i)->is_new)
                    {
                        int tmp_znach = 0;
                        if (string_to_int(znach[j], &tmp_znach) != 0)
                            return ERROR;
                        if (((*car_list)+i)->condition.old_car_params.owners_count != tmp_znach)
                            flag = false;
                    }
                }
                    break;
                default:
                    return ERROR;
                    break;
                }
        }

        if (flag)
            print_car_record(*((*car_list)+i));
    }
    return 0;
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
    //int *key_list = new int[size_of_list];
    car *cars_list = new car [size_of_list];

    string inp = "";
    car car_record;
    inp = "Valve; Russia; 1 000 000; black; new; 2022;";
    read_record(inp, &cars_list[0]);
    /*inp = "Steam; America; 2 000 000; white; old; 2022; 44000; 44; 22;";
    read_record(inp, &cars_list[1]);
    inp = "Valve2; Russia; 1 000 000; black; new; 2022;";
    read_record(inp, &cars_list[2]);
    print_car_list(cars_list, size_of_list);*/

    inp = "Steam; America; 2 000 000; white; old; 2024; 44000; 44; 22;";
    cout << read_record(inp, &car_record) << endl;

    print_car_list(cars_list, size_of_list);

    size_of_list = add_record(&cars_list, size_of_list, car_record);

    print_car_list(cars_list, size_of_list);

    cout << size_of_list << endl;

    //size_of_list = delete_record(&cars_list, size_of_list, 1);
    if (print_car_record_by_pole(OWNERS_COUNT, "22", &cars_list, size_of_list) != -1) //Error when "Steam"
        cout << size_of_list << endl;
    if (size_of_list != -1)
    {
        print_car_list(cars_list, size_of_list);
    }

    int test1[10] = {1, 2, 3, 4, 5, 0, 7, 8, 9, 10};
    string test2[10] = {"Steam", "America", "2000000", "white", "old", "2022", "2024", "44000", "44", "22"};

    print_car_record_by_poles(test1, test2, &cars_list, size_of_list);

    //print_car_list(cars_list, size_of_list);

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
