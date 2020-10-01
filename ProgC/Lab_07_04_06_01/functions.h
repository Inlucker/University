#ifndef FUNCTIONS_H
#define FUNCTIONS_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 10
#define M 100
#define L 25
#define CONSOLE_ARGS_ERROR -1
#define FILE_READ_ERROR -2
#define MEMORY_ERROR -3
#define FILE_OUTPUT_ERROR -4
#define FILTR_ERROR -5

/*
#define SWAP(a, b, size)                                                      \
  do                                                                              \
    {                                                                              \
      size_t __size = (size);                                                      \
      char *__a = (a), *__b = (b);                                              \
      do                                                                      \
        {                                                                      \
          char __tmp = *__a;                                                      \
          *__a++ = *__b;                                                      \
          *__b++ = __tmp;                                                      \
        } while (--__size > 0);                                                      \
    } while (0)
*/

//void swap_int(int *a, int *b);

//int puz_sort(int *mas, int n);

//double ** allocate_matrix_2(int n, int m);

void swap(void *a, void *b, size_t size_of_type);

int comp_int(const int *i, const int *j);

int comp_float(const float *i, const float *j);

int comp_char(const char *i, const char *j);

int comp_string(const char *i, const char *j);

int mysort(void *mas, size_t size_of_mas, size_t size_of_type, int ( * comparator ) ( const void *, const void * ));

int key(const int *pb_src, const int *pe_src, int **pb_dst, int **pe_dst);

int read_file_n(char *file_name, int *n);

int read_file(char *file_name, int *mas, int n);

int read_args(int argc, char **argv, int *filtr, char *input_file_name, char *output_file_name);

int output(char *file_name, int *mas, int n);

#endif // FUNCTIONS_H
