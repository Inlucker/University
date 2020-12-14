#include "comporators.h"

int comp_int(const int *i, const int *j)
{
    return *i - *j;
}

int comp_double(const double *i, const double *j)
{
    int rez = 0;
    if (*i - *j > EPS)
        rez = 1;
    else if (*j - *i > EPS)
        rez = -1;
    return rez;
}

int comp_char(const char *i, const char *j)
{
    int rez = 0;
    char tmp1 = *i;
    char tmp2 = *j;
    if (tmp1 < 'a')
        tmp1 += 'a' - 'A';

    if (tmp2 < 'a')
        tmp2 += 'a' - 'A';

    if (tmp1 < tmp2)
        rez = -1;
    else if (tmp1 > tmp2)
        rez = 1;
    else
        rez = 0;
    return rez;
}

int comp_info(const node_t *i, const node_t *j)
{
    info_t *tmp_data1 = i->data;
    info_t *tmp_data2 = j->data;
    int rez = comp_char(&tmp_data1->name, &tmp_data2->name);
    if (rez != 0)
        return rez;
    rez = comp_int(&tmp_data1->years, &tmp_data2->years);
    if (rez != 0)
        return rez;
    rez = comp_double(&tmp_data1->intelect, &tmp_data2->intelect);
    return rez;
}
