#include "car_list_funcs.h"

//no need
void print_key_list(int *key_list, int size_of_list)
{
    for (int i = 0; i < size_of_list; i++)
    {
        cout << i + 1 << ": ";
        cout << key_list[i] << endl;
    }
    cout << endl;
}

void print_price_key_list(price_keys *key_list, int size_of_list)
{
    for (int i = 0; i < size_of_list; i++)
    {
        //cout << i + 1 << ": ";
        cout << key_list[i].id << "; " << key_list[i].price << "; " << endl;
    }
    cout << endl;
}

void print_car_list(car *cars_list, int size_of_list)
{
    for (int i = 0; i < size_of_list; i++)
    {
        //cout << i + 1 << ": ";
        print_car_record(cars_list[i]);
    }
    cout << endl;
}

void print_car_list_by_keys(car *cars_list, int size_of_list, int *key_list)
{
    for (int i = 0; i < size_of_list; i++)
    {
        //cout << i + 1 << ": ";
        print_car_record(cars_list[key_list[i]]);
    }
    cout << endl;
}

void print_car_list_by_price_keys(car *cars_list, int size_of_list, price_keys *key_list)
{
    for (int i = 0; i < size_of_list; i++)
    {
        //cout << i + 1 << ": ";
        print_car_record(cars_list[key_list[i].id]);
    }
    cout << endl;
}

void car_list_copy (car *car_list1, car *car_list2, int size_of_list)
{
    for (int i = 0; i < size_of_list; i++)
        car_list1[i] = car_list2[i];
}

int add_record (car **car_list, int size_of_list, car car_record)
{
    car *cars_list_new = new car [size_of_list + 1];
    car_list_copy(cars_list_new, *car_list, size_of_list);
    cars_list_new[size_of_list] = car_record;

    delete[] *car_list;
    *car_list = new car[size_of_list + 1];
    car_list_copy(*car_list, cars_list_new, size_of_list + 1);

    delete [] cars_list_new;

    return size_of_list + 1;
}

int read_file(string file_name, car **car_list, int *size_of_list)
{
    ifstream f(file_name);
    string input = "";
    car car_record;
    while(getline(f, input))
    {
        if (read_record(input, &car_record) == 0)
            *size_of_list = add_record(car_list, *size_of_list, car_record);
    }
    return 0;
}

void car_record_copy(car *car_list1, car *car_list2, int i)
{
    car_list1[i] = car_list2[i+1];
}

int delete_record(car **car_list, int size_of_list, int id)
{
    if (id > size_of_list && id <= 0)
        return -1;
    car *cars_list_new = new car [size_of_list - 1];
    car_list_copy(cars_list_new, *car_list, id - 1);
    for (int i = id - 1; i < size_of_list - 1; i++)
        car_record_copy(cars_list_new, *car_list, i);

    delete[] *car_list;
    *car_list = new car[size_of_list - 1];
    car_list_copy(*car_list, cars_list_new, size_of_list - 1);

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
    cout << endl;
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
    cout << endl;
    return 0;
}
