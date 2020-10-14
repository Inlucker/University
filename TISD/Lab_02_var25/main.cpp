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

    /*int *key_list = new int [size_of_list];
    for (int i = 0; i < size_of_list; i++)
        key_list[i] = i;*/

    price_keys *price_key_list = new price_keys [size_of_list];
    for (int i = 0; i < size_of_list; i++)
    {
        price_key_list[i].id = i;
        price_key_list[i].price = cars_list[i].price;
    }
    int input = -1;

    while (input != 0)
    {
        cout << endl;
        cout << "1 - Print car_list" << endl;
        cout << "2 - Add record to car_list" << endl;
        cout << "3 - Delete record from car_list by ID" << endl;
        cout << "4 - Delete records from car_list by field value" << endl;
        cout << "5 - Print car_list by field's values" << endl;
        cout << "6 - Print key_list" << endl;
        cout << "7 - Print car_list using key_list" << endl;
        cout << "8 - BubbleSort car_list by field" << endl;
        cout << "9 - BubbleSort price_key_list" << endl;
        cout << "10 - QuickSort price_key_list" << endl;
        cout << "11 - QuickSort car_list by field" << endl;
        cout << "12 - Time Tests for sorts" << endl;
        cout << "0 - Exit from programm" << endl;
        cout << endl;

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
            print_car_list(cars_list, size_of_list);
            break;
        }
        case 2:
        {
            _flushall();
            cout << "Enter record in format:\nBrand; Country; price; color; new/old; guarantee/year_of_release; probeg; repair_count; owners_count;" << endl;
            string input_str = "";
            getline(cin, input_str);
            //cout << input_str << endl;
            car car_record;
            if (read_record(input_str, &car_record) == 0)
            {
                size_of_list = add_record(&cars_list, size_of_list, car_record);
                if (size_of_list == -1)
                {
                    cout << "Adding error, exiting from programm..." << endl;
                    delete [] price_key_list;
                    delete [] cars_list;
                    return ERROR;
                }
                delete [] price_key_list;
                price_key_list = new price_keys [size_of_list];
                for (int i = 0; i < size_of_list; i++)
                {
                    price_key_list[i].id = i;
                    price_key_list[i].price = cars_list[i].price;
                }
            }
            else
            {
                cout << "Invalid input" << endl;
            }
            break;
        }
        case 3:
        {
            _flushall();
            cout << "Enter ID of record to delete: ";
            int id = -1;
            cin >> id;
            if (id > 0 && id <= size_of_list)
                size_of_list = delete_record(&cars_list, size_of_list, id);
            else
                cout << "Invalid input" << endl;
            break;
        }
        case 4:
        {
            _flushall();
            cout << "Enter field number (BRAND = 0, MANUFACURER_COUNTRY = 1, PRICE = 2, COLOR = 3, IS_NEW = 4, GUARANTEE = 5, YEAR_OF_RELEASE = 6, PROBEG = 7, REPAIR_COUNT = 8, OWNERS_COUNT = 9): ";
            int field_number = -1;
            if (!(cin >> field_number))
            {
                cout << "Invalid input" << endl;
                cin.clear();
                break;
            }
            if (field_number < 0 || field_number > 9)
            {
                cout << "Invalid input" << endl;
                break;
            }
            _flushall();
            cout << "Enter field value:" << endl;
            string input_str = "";
            getline(cin, input_str);
            if (delete_car_record_by_pole(field_number, input_str, &cars_list, &size_of_list) != 0)
            {
                cout << "Invalid input" << endl;
            }
            break;
        }
        case 5:
        {
            int fields[10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
            _flushall();
            cout << "Enter field's numbers (BRAND = 0, MANUFACURER_COUNTRY = 1, PRICE = 2, COLOR = 3, IS_NEW = 4, GUARANTEE = 5, YEAR_OF_RELEASE = 6, PROBEG = 7, REPAIR_COUNT = 8, OWNERS_COUNT = 9): ";
            string input_str = "";
            getline(cin, input_str);
            bool flag = false;
            for (int i = 0; i < input_str.length(); i++)
            {
                if (int(input_str[i]) >= '0' && int(input_str[i]) <= '9')
                {
                    fields[int(input_str[i] - '0')] = 1;
                }
                else if (int(input_str[i]) != ' ')
                {
                    cout << "Invalid input" << endl;
                    flag = true;
                    break;
                }
            }
            if (flag)
                break;
            string fields_values[10] = {"", "", "", "", "", "", "", "", "", ""};
            for (int i = 0; i < 10; i++)
            {
                if (fields[i])
                {
                    _flushall();
                    cout << "Enter value for field #" << i << ": " << endl;
                    getline(cin, fields_values[i]);
                }
            }
            if (print_car_record_by_poles(fields, fields_values, &cars_list, size_of_list) != 0)
            {
                cout << "Invalid input" << endl;
            }
            break;
        }
        case 6:
        {
            print_price_key_list(price_key_list, size_of_list);
            break;
        }
        case 7:
        {
            print_car_list_by_price_keys(cars_list, size_of_list, price_key_list);
            break;
        }
        case 8:
        {
            _flushall();
            cout << "Enter field number (BRAND = 0, MANUFACURER_COUNTRY = 1, PRICE = 2, COLOR = 3, IS_NEW = 4, GUARANTEE = 5, YEAR_OF_RELEASE = 6, PROBEG = 7, REPAIR_COUNT = 8, OWNERS_COUNT = 9): ";
            int field_number = -1;
            if (!(cin >> field_number))
            {
                cout << "Invalid input" << endl;
                cin.clear();
                break;
            }
            switch (field_number)
            {
            case BRAND:
                car_sort_puz(&cars_list, size_of_list, (int(*)(const car*, const car*))comp_car_brand);
                break;
            case MANUFACURER_COUNTRY:
                car_sort_puz(&cars_list, size_of_list, (int(*)(const car*, const car*))comp_car_manufacturer_country);
                break;
            case PRICE:
                car_sort_puz(&cars_list, size_of_list, (int(*)(const car*, const car*))comp_car_price);
                break;
            case COLOR:
                car_sort_puz(&cars_list, size_of_list, (int(*)(const car*, const car*))comp_car_color);
                break;
            case IS_NEW:
                car_sort_puz(&cars_list, size_of_list, (int(*)(const car*, const car*))comp_car_is_new);
                break;
            case GUARANTEE:
                car_sort_puz(&cars_list, size_of_list, (int(*)(const car*, const car*))comp_car_guarantee);
                break;
            case YEAR_OF_RELEASE:
                car_sort_puz(&cars_list, size_of_list, (int(*)(const car*, const car*))comp_car_year_of_release);
                break;
            case PROBEG:
                car_sort_puz(&cars_list, size_of_list, (int(*)(const car*, const car*))comp_car_probeg);
                break;
            case REPAIR_COUNT:
                car_sort_puz(&cars_list, size_of_list, (int(*)(const car*, const car*))comp_car_repair_count);
                break;
            case OWNERS_COUNT:
                car_sort_puz(&cars_list, size_of_list, (int(*)(const car*, const car*))comp_car_owners_count);
                break;
            default:
                cout << "Invalid input" << endl;
                break;
            }
            break;
        }
        case 9:
        {
            /*_flushall();
            cout << "Enter field number (BRAND = 0, MANUFACURER_COUNTRY = 1, PRICE = 2, COLOR = 3, IS_NEW = 4, GUARANTEE = 5, YEAR_OF_RELEASE = 6, PROBEG = 7, REPAIR_COUNT = 8, OWNERS_COUNT = 9): ";
            int field_number = -1;
            cin >> field_number;
            switch (field_number)
            {
            case BRAND:
                car_sort_puz_by_keys(&cars_list, size_of_list, (int(*)(const car*, const car*))comp_car_brand, &key_list);
                break;
            case MANUFACURER_COUNTRY:
                car_sort_puz_by_keys(&cars_list, size_of_list, (int(*)(const car*, const car*))comp_car_manufacturer_country, &key_list);
                break;
            case PRICE:
                car_sort_puz_by_keys(&cars_list, size_of_list, (int(*)(const car*, const car*))comp_car_price, &key_list);
                break;
            case COLOR:
                car_sort_puz_by_keys(&cars_list, size_of_list, (int(*)(const car*, const car*))comp_car_color, &key_list);
                break;
            case IS_NEW:
                car_sort_puz_by_keys(&cars_list, size_of_list, (int(*)(const car*, const car*))comp_car_is_new, &key_list);
                break;
            case GUARANTEE:
                car_sort_puz_by_keys(&cars_list, size_of_list, (int(*)(const car*, const car*))comp_car_guarantee, &key_list);
                break;
            case YEAR_OF_RELEASE:
                car_sort_puz_by_keys(&cars_list, size_of_list, (int(*)(const car*, const car*))comp_car_year_of_release, &key_list);
                break;
            case PROBEG:
                car_sort_puz_by_keys(&cars_list, size_of_list, (int(*)(const car*, const car*))comp_car_probeg, &key_list);
                break;
            case REPAIR_COUNT:
                car_sort_puz_by_keys(&cars_list, size_of_list, (int(*)(const car*, const car*))comp_car_repair_count, &key_list);
                break;
            case OWNERS_COUNT:
                car_sort_puz_by_keys(&cars_list, size_of_list, (int(*)(const car*, const car*))comp_car_owners_count, &key_list);
                break;
            default:
                cout << "Invalid input" << endl;
                break;
            }*/
            price_keys_sort_puz(&price_key_list, size_of_list);
            break;
        }
        case 10:
        {
            price_keys_sort_qsort(price_key_list, 0, size_of_list - 1);
            break;
        }
        case 11:
        {
            _flushall();
            cout << "Enter field number (BRAND = 0, MANUFACURER_COUNTRY = 1, PRICE = 2, COLOR = 3, IS_NEW = 4, GUARANTEE = 5, YEAR_OF_RELEASE = 6, PROBEG = 7, REPAIR_COUNT = 8, OWNERS_COUNT = 9): ";
            int field_number = -1;
            if (!(cin >> field_number))
            {
                cout << "Invalid input" << endl;
                cin.clear();
                break;
            }
            switch (field_number)
            {
            case BRAND:
                car_sort_qsort(cars_list, 0, size_of_list - 1, (int(*)(const car*, const car*))comp_car_brand);
                break;
            case MANUFACURER_COUNTRY:
                car_sort_qsort(cars_list, 0, size_of_list - 1, (int(*)(const car*, const car*))comp_car_manufacturer_country);
                break;
            case PRICE:
                car_sort_qsort(cars_list, 0, size_of_list - 1, (int(*)(const car*, const car*))comp_car_price);
                break;
            case COLOR:
                car_sort_qsort(cars_list, 0, size_of_list - 1, (int(*)(const car*, const car*))comp_car_color);
                break;
            case IS_NEW:
                car_sort_qsort(cars_list, 0, size_of_list - 1, (int(*)(const car*, const car*))comp_car_is_new);
                break;
            case GUARANTEE:
                car_sort_qsort(cars_list, 0, size_of_list - 1, (int(*)(const car*, const car*))comp_car_guarantee);
                break;
            case YEAR_OF_RELEASE:
                car_sort_qsort(cars_list, 0, size_of_list - 1, (int(*)(const car*, const car*))comp_car_year_of_release);
                break;
            case PROBEG:
                car_sort_qsort(cars_list, 0, size_of_list - 1, (int(*)(const car*, const car*))comp_car_probeg);
                break;
            case REPAIR_COUNT:
                car_sort_qsort(cars_list, 0, size_of_list - 1, (int(*)(const car*, const car*))comp_car_repair_count);
                break;
            case OWNERS_COUNT:
                car_sort_qsort(cars_list, 0, size_of_list - 1, (int(*)(const car*, const car*))comp_car_owners_count);
                break;
            default:
                cout << "Invalid input" << endl;
                break;
            }
            break;
        }
        case 12:
        {
            _flushall();
            cout << "Enter mnojitel of iterations: ";
            int mn = 0;
            cin >> mn;
            int tmp_size_of_list = 0;
            car *tmp_cars_list = new car [tmp_size_of_list];

            string input_file_name = "car_list.txt";
            if (read_file(input_file_name, &tmp_cars_list, &tmp_size_of_list) != 0)
                return ERROR;

            price_keys *tmp_price_key_list = new price_keys [tmp_size_of_list];
            for (int i = 0; i < tmp_size_of_list; i++)
            {
                price_key_list[i].id = i;
                price_key_list[i].price = cars_list[i].price;
            }
            car_sort_puz_test(&tmp_cars_list, tmp_size_of_list, comp_car_price, mn);
            price_keys_sort_puz_test(&tmp_price_key_list, tmp_size_of_list, mn);
            car_sort_qsort_test(tmp_cars_list, 0, tmp_size_of_list - 1, comp_car_price, mn);
            price_keys_sort_qsort_test(tmp_price_key_list, 0, tmp_size_of_list - 1, mn);
            delete [] tmp_cars_list;
            delete [] tmp_price_key_list;
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

    /*cout << size_of_list << endl;

    //car_sort_puz(&cars_list, size_of_list, (int(*)(const car*, const car*))comp_car_price);
    //car_sort_qsort(&cars_list, size_of_list, (int(*)(const car*, const car*))comp_car_price);
    car_sort_puz_by_keys(&cars_list, size_of_list, (int(*)(const car*, const car*))comp_car_brand, &key_list);

    print_key_list(key_list, size_of_list);
    print_car_list_by_keys(cars_list, size_of_list, key_list);

    car_sort_puz(&cars_list, size_of_list, (int(*)(const car*, const car*))comp_car_brand);

    print_car_list(cars_list, size_of_list);*/

    delete [] cars_list;
    //delete [] key_list;
    delete [] price_key_list;
    //cout << "OK" << endl;

    return 0;
}
