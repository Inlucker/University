#ifndef SORT_FUNCS_H
#define SORT_FUNCS_H

#include <stdio.h>

void swap(void *a, void *b, size_t size_of_type);

int comp_int(const int *i, const int *j);

int comp_double(const double *i, const double *j);

int comp_char(const char *i, const char *j);

int mysort(void *mas, size_t size_of_mas, size_t size_of_type, int(*comparator)(const void *, const void *));

#endif // SORT_FUNCS_H
