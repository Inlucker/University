#include "comporators.h"

int comp_string(const string *str1, const string *str2)
{
    size_t min_size = str1->length();
    string tmp1 = *str1;
    string tmp2 = *str2;
    int rez = 0;
    if (str2->length() < min_size)
        min_size = str2->length();
    for (size_t i = 0; i < min_size; i++)
    {
        if (tmp1[i] < 'a')
            tmp1[i] += 'a' - 'A';

        if (tmp2[i] < 'a')
            tmp2[i] += 'a' - 'A';

        if(tmp1[i] < tmp2[i])
            rez = -1;
        else if (tmp1[i] > tmp2[i])
            rez = 1;
        else
            rez = 0;
        if (rez != 0)
            break;
    }
    return rez;
}
