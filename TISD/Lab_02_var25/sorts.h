#ifndef SORTS_H
#define SORTS_H

#include "structs.h"

void swap_car_records(car *car_list1, car *car_list2);

void swap_keys(int *key1, int *key2);

void car_sort_puz(car **mas, int size_of_mas, int (*comparator)(const car*, const car*));

void car_sort_puz_by_keys(car **mas, int size_of_mas, int (*comparator)(const car*, const car*), int **keys);

void car_sort_qsort(car **mas, int size_of_mas, int (*comparator)(const car*, const car*));

void car_sort_qsort_by_keys(car **mas, int size_of_mas, int (*comparator)(const car*, const car*), int **keys);

struct thing
{
    char name[25];
    float m;
    float v;
    float p;
};

void quick_sort(struct thing *a, int l, int r);

#endif // SORTS_H
