#ifndef SORTS_H
#define SORTS_H

#include "structs.h"

void swap_car_records(car *car_list1, car *car_list2);

void car_sort_puz(car **mas, int size_of_mas, int (*comparator)(const car*, const car*));

#endif // SORTS_H
