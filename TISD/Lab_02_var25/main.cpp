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
        cout << "8 - Sort car_list by filed value" << endl;
        cout << "9 - Sort key_list by filed value" << endl;
        cout << "0 - Exit from programm" << endl;
        cout << endl;

        cout << "Enter the number of command to be done: ";

        cin >> input;

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
            cout << "Enter record in format():" << endl;
            string input_str = "";
            getline(cin, input_str);
            cout << input_str << endl;
            car car_record;
            if (read_record(input_str, &car_record) == 0)
            {
                size_of_list = add_record(&cars_list, size_of_list, car_record);
                if (size_of_list == -1)
                {
                    cout << "Adding error, exiting from programm..." << endl;
                    delete [] cars_list;
                    return ERROR;
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
            cout << "Enter ID of record to delete: ";
            int id = -1;
            cin >> id;
            size_of_list = delete_record(&cars_list, size_of_list, id);
            break;
        }
        case 4:
        {
            cout << "Enter field number (BRAND = 0, MANUFACURER_COUNTRY = 1, PRICE = 2, COLOR = 3, IS_NEW = 4, GUARANTEE = 5, YEAR_OF_RELEASE = 6, PROBEG = 7, REPAIR_COUNT = 8, OWNERS_COUNT = 9): ";
            int field_number = -1;
            cin >> field_number;
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
            print_key_list(key_list, size_of_list);
            break;
        }
        case 7:
        {
            print_car_list_by_keys(cars_list, size_of_list, key_list);
            break;
        }
        case 8:
        {
            cout << "Enter field number (BRAND = 0, MANUFACURER_COUNTRY = 1, PRICE = 2, COLOR = 3, IS_NEW = 4, GUARANTEE = 5, YEAR_OF_RELEASE = 6, PROBEG = 7, REPAIR_COUNT = 8, OWNERS_COUNT = 9): ";
            int field_number = -1;
            cin >> field_number;
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
            }
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
    //cout << "OK" << endl;

    return 0;
}
