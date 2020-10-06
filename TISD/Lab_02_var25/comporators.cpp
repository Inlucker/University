#include "comporators.h"

int comp_int(const int *i, const int *j)
{
    return *i - *j;
}

int comp_string(const string *str1, const string *str2)
{
    size_t min_size = str1->length();
    string tmp1 = *str1;
    string tmp2 = *str2;
    int rez = 0;
    if (str2->length() < min_size)
        min_size = str2->length();
    for (size_t i = 0; i < min_size; i++)
    {
        if (tmp1[i] < 'a')
            tmp1[i] += 'a' - 'A';

        if (tmp2[i] < 'a')
            tmp2[i] += 'a' - 'A';

        if(tmp1[i] < tmp2[i])
            rez = -1;
        else if (tmp1 > tmp2)
            rez = 1;
        else
            rez = 0;
        if (rez != 0)
            break;
    }
    return rez;
}

int comp_car_brand(const car *i, const car *j)
{
    return comp_string(&i->brand, &j->brand);
}

int comp_car_manufacturer_country(const car *i, const car *j)
{
    return comp_string(&i->manufacturer_country, &j->manufacturer_country);
}

int comp_car_price(const car *i, const car *j)
{
    return i->price - j->price;
}

int comp_car_color(const car *i, const car *j)
{
    return comp_string(&i->color, &j->color);
}

int comp_car_is_new(const car *i, const car *j)
{
    return -i->is_new + j->is_new;
}

int comp_car_guarantee(const car *i, const car *j)
{
    if (i->is_new && j->is_new)
    {
        return i->condition.new_car_params.guarantee - j->condition.new_car_params.guarantee;
    }
    else if (i->is_new && !j->is_new)
    {
        return -1;
    }
    else if (!i->is_new && j->is_new)
    {
        return 1;
    }
    else
    {
        return 0;
    }

}

int comp_car_year_of_release(const car *i, const car *j)
{
    if (!i->is_new && !j->is_new)
    {
        return i->condition.old_car_params.year_of_release - j->condition.old_car_params.year_of_release;
    }
    else if (i->is_new && !j->is_new)
    {
        return 1;
    }
    else if (!i->is_new && j->is_new)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int comp_car_probeg(const car *i, const car *j)
{
    if (!i->is_new && !j->is_new)
    {
        return i->condition.old_car_params.probeg - j->condition.old_car_params.probeg;
    }
    else if (i->is_new && !j->is_new)
    {
        return 1;
    }
    else if (!i->is_new && j->is_new)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int comp_car_repair_count(const car *i, const car *j)
{
    if (!i->is_new && !j->is_new)
    {
        return i->condition.old_car_params.repair_count - j->condition.old_car_params.repair_count;
    }
    else if (i->is_new && !j->is_new)
    {
        return 1;
    }
    else if (!i->is_new && j->is_new)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}

int comp_car_owners_count(const car *i, const car *j)
{
    if (!i->is_new && !j->is_new)
    {
        return i->condition.old_car_params.owners_count - j->condition.old_car_params.owners_count;
    }
    else if (i->is_new && !j->is_new)
    {
        return 1;
    }
    else if (!i->is_new && j->is_new)
    {
        return -1;
    }
    else
    {
        return 0;
    }
}
