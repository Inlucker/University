#include "sorts.h"

void swap_car_records(car *car_list1, car *car_list2)
{
    car tmp_car = *car_list1;
    *car_list1 = *car_list2;
    *car_list2 = tmp_car;
}

void swap_keys(int *key1, int *key2)
{
    int tmp_key = *key1;
    *key1 = *key2;
    *key2 = tmp_key;
}

void car_sort_puz(car **mas, int size_of_mas, int (*comparator)(const car*, const car*))
{
    for (int i = 0; i < size_of_mas; i++)
        if (i % 2 == 0)
        {
            for (int j = size_of_mas - 1; j > 0; j--)
                if (comparator(((*mas) + j - 1), ((*mas) + j)) > 0)
                    swap_car_records(((*mas) + j - 1), ((*mas) + j));
        }
        else
        {
            for (int j = 0; j < size_of_mas - 1; j++)
                if (comparator(((*mas) + j + 1), ((*mas) + j)) < 0)
                    swap_car_records(((*mas) + j + 1), ((*mas) + j));
        }
}

void car_sort_puz_by_keys(car **mas, int size_of_mas, int (*comparator)(const car*, const car*), int **keys)
{
    for (int i = 0; i < size_of_mas; i++)
        if (i % 2 == 0)
        {
            for (int j = size_of_mas - 1; j > 0; j--)
                if (comparator(((*mas) + *((*keys) + j - 1)), ((*mas) + *((*keys) + j))) > 0)
                    swap_keys(((*keys) + j - 1), ((*keys) + j));
        }
        else
        {
            for (int j = 0; j < size_of_mas - 1; j++)
                if (comparator(((*mas) + *((*keys) + j + 1)), ((*mas) + *((*keys) + j))) < 0)
                    swap_keys(((*keys) + j + 1), ((*keys) + j));
        }
}

//not done
void car_sort_qsort(car **mas, int size_of_mas, int (*comparator)(const car*, const car*))
{
    car *base_ptr = *mas;

    if (size_of_mas == 0)
        return;

    car *l = base_ptr;
    car *r = (*mas + size_of_mas - 1);

    car *i = l;
    car *j = r;
    car *m = ((*mas) + (size_of_mas/2));
    do
    {
        for (; comparator(i, m) < 0; i++);
        for (; comparator(j, m) > 0; j--);
        if (i <= j)
        {
            swap_car_records(i, j);
            i++;
            j--;
        }
    }while (i <= j);
    if (l < j)
        car_sort_qsort(mas, size_of_mas, (int(*)(const car*, const car*))comparator);
    if (i < r)
        car_sort_qsort(mas, size_of_mas, (int(*)(const car*, const car*))comparator);
}

//not done
void car_sort_qsort_by_keys(car **mas, int size_of_mas, int (*comparator)(const car*, const car*), int **keys)
{

}

void quick_sort(struct thing *a, int l, int r)
{
    int i = l, j = r;
    float m = a[(l + r) / 2].p;
    do
    {
        for (; a[i].p < m; i++);
        for (; a[j].p > m; j--);
        if (i <= j)
        {
            struct thing tmp = a[i];
            a[i] = a[j];
            a[j] = tmp;
            i++;
            j--;
        }
    }while (i <= j);
    if (l < j)
        quick_sort(a, l, j);
    if (i < r)
        quick_sort(a, i, r);
};
