#ifndef SORT_FUNCS_H
#define SORT_FUNCS_H

#include <stdio.h>

void swap(void *a, void *b, size_t size_of_type);

int comp_int(const int *i, const int *j);

int comp_double(const double *i, const double *j);

int comp_char(const char *i, const char *j);

int mysort(void *mas, size_t size_of_mas, size_t size_of_type, int(*comparator)(const void *, const void *));

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

#endif // SORT_FUNCS_H
