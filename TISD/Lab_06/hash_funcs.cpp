#include "hash_funcs.h"

int my_hash(string key, int m)
{
    int rez = 0;
    for (int i = 0; i < key.length(); i ++)
    {
        rez += key[i];
    }
    return rez % m;
}
