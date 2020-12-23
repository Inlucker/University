#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include "defines.h"

void print_mas(int n, int *mas);

void print_mas_char(int n, char *mas);

void print_mas_double(int n, double *mas);

void swap(void *a, void *b, size_t size_of_type);

int comp_int(const int *i, const int *j);

int comp_double(const double *i, const double *j);

int comp_char(const char *i, const char *j);

int mysort(void *mas, size_t size_of_mas, size_t size_of_type, int(*comparator)(const void *, const void *));

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

/*int read_file_n(char *file_name, int *n);

int read_file(char *file_name, int *mas);

int read_args(int argc, char **argv, int *filtr, char *input_file_name, char *output_file_name);

int output(char *file_name, int *mas, int n);*/

#endif // FUNCTIONS_H
