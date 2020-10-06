#ifndef CAR_LIST_FUNCS_H
#define CAR_LIST_FUNCS_H
#include "structs.h"

void print_car_list(car *cars_list, int size_of_list);

void car_list_copy (car *car_list1, car *car_list2, int size_of_list);

int add_record (car **car_list, int size_of_list, car car_record);

int read_file(string file_name, car **car_list, int *size_of_list);

void car_record_copy (car *car_list1, car *car_list2, int i); //?

int delete_record (car **car_list, int size_of_list, int id);

int delete_car_record_by_pole(int pole, string znach, car **car_list, int *size_of_list);

int print_car_record_by_pole(int pole, string znach, car **car_list, int size_of_list); //no need

int print_car_record_by_poles(int pole[10], string znach[10], car **car_list, int size_of_list);

#endif // CAR_LIST_FUNCS_H
