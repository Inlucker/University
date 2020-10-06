#ifndef SORTS_H
#define SORTS_H

#include "structs.h"
#include <ctime>

void swap_car_records(car *car_list1, car *car_list2);

void swap_keys(int *key1, int *key2);//no need

void car_sort_puz(car **mas, int size_of_mas, int (*comparator)(const car*, const car*));

void car_sort_puz_by_keys(car **mas, int size_of_mas, int (*comparator)(const car*, const car*), int **keys); //no need

void price_keys_sort_puz(price_keys **mas, int size_of_mas);

void price_keys_sort_qsort(price_keys *a, int l, int r);

void car_sort_qsort(car *a, int l, int r, int (*comparator)(const car*, const car*));

void car_sort_puz_test(car **mas, int size_of_mas, int (*comparator)(const car*, const car*), int mn);

void price_keys_sort_puz_test(price_keys **mas, int size_of_mas, int mn);

void price_keys_sort_qsort_test(price_keys *a, int l, int r, int mn);

void car_sort_qsort_test(car *a, int l, int r, int (*comparator)(const car*, const car*), int mn);

#endif // SORTS_H
