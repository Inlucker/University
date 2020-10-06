#ifndef COMPORATORS_H
#define COMPORATORS_H

#include "structs.h"

int comp_int(const int *i, const int *j); //no need

int comp_string(const string *str1, const string *str2);

int comp_car_brand(const car *i, const car *j);

int comp_car_manufacturer_country(const car *i, const car *j);

int comp_car_price(const car *i, const car *j);

int comp_car_color(const car *i, const car *j);

int comp_car_is_new(const car *i, const car *j);

#endif // COMPORATORS_H
