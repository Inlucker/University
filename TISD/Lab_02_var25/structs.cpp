#include <structs.h>

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
    if (input.length() <= 0)
        return ERROR;
    int i = 0;
    car car_record;
    int j = 0;
    while (j < input.length())
    {
        string tmp = "";
        while (input[j] != ';' && j < input.length())
        {
            if (input[j] != ' ')
                tmp += input[j];
            j++;
        }
        if (j >= input.length())
            return ERROR;
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
