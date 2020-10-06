#ifndef STRUCTS_H
#define STRUCTS_H

#include <iostream>
#include <cstring>
//#include <string>
#include <fstream>

#define ERROR -1;

using namespace std;

enum
{
    BRAND = 0,
    MANUFACURER_COUNTRY = 1,
    PRICE = 2,
    COLOR = 3,
    IS_NEW = 4,
    GUARANTEE = 5,
    YEAR_OF_RELEASE = 6,
    PROBEG = 7,
    REPAIR_COUNT = 8,
    OWNERS_COUNT = 9
};

struct new_car
{
    int guarantee;
};

struct old_car
{
    int year_of_release;
    int probeg;
    int repair_count;
    int owners_count;
};

union state
{
    new_car new_car_params;
    old_car old_car_params;
};

struct car
{
    string brand;
    string manufacturer_country;
    int price;
    string color;
    bool is_new;
    state condition;
};

struct price_keys
{
    int id;
    int price;
};

int string_to_int(string input, int *rez);

int read_record (string input, car *car_record_rez);

void print_car_record(car car_record);


#endif //STRUCTS_H
