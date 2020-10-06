#include "sorts.h"

void swap_car_records(car *car_list1, car *car_list2)
{
    car tmp_car = *car_list1;
    *car_list1 = *car_list2;
    *car_list2 = tmp_car;
}

void car_sort_puz(car **mas, int size_of_mas, int (*comparator)(const car*, const car*))
{
    for (int i = 0; i < size_of_mas; i++)
        if (i % 2 == 0)
        {
            for (int j = size_of_mas - 1; j > 0; j--)
                if (comparator(((*mas) + j - 1), (*mas) + j) > 0)
                {
                    swap_car_records(((*mas) + j - 1), (((*mas) + j)));
                }
        }
        else
        {
            for (int j = 0; j < size_of_mas - 1; j++)
                if (comparator(((*mas) + j + 1), (*mas) + j) < 0)
                {
                    swap_car_records(((*mas) + j + 1), (((*mas) + j)));
                }
        }
}
