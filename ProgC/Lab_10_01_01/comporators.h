#ifndef COMPORATORS_H
#define COMPORATORS_H

#include "defines.h"

int comp_int(const int *i, const int *j);

int comp_double(const double *i, const double *j);

int comp_char(const char *i, const char *j);

int comp_string(const char *i, const char *j);

int comp_node(const node_t *i, const node_t *j);

int comp_info(const info_t *i, const info_t *j);

#endif // COMPORATORS_H
