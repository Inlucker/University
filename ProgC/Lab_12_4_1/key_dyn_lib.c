#include "key_dyn_lib.h"
#include <stdio.h>
#include <stdlib.h>

#define ARR_EXPORT

ARR_DLL int ARR_DECL key(const int *pb_src, const int *pe_src, int *pb_dst, float sr, int m)
{
    if (pb_src >= pe_src)
        return FILTR_ERROR;
    int *mas_f = pb_dst;

    if (m == 0)
        return FILTR_ERROR;

    if (!mas_f)
        return MEMORY_ERROR;

    int j = 0;
    const int *pa = pb_src;
    for (pa = pb_src; pa < pe_src; pa++)
    {
        if (*pa > sr)
        {
            mas_f[j] = *pa;
            j++;
            if (j > m)
                return FILTR_ERROR;
        }
    }

    return 0;
}
