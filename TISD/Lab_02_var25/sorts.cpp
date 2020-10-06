#include "sorts.h"

void swap_car_records(car *car_list1, car *car_list2)
{
    car tmp_car = *car_list1;
    *car_list1 = *car_list2;
    *car_list2 = tmp_car;
}

//no need
void swap_keys(int *key1, int *key2)
{
    int tmp_key = *key1;
    *key1 = *key2;
    *key2 = tmp_key;
}

void swap_price_keys(price_keys *key1, price_keys *key2)
{
    price_keys tmp_key = *key1;
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

//no need
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

void price_keys_sort_puz(price_keys **mas, int size_of_mas)
{
    for (int i = 0; i < size_of_mas; i++)
        if (i % 2 == 0)
        {
            for (int j = size_of_mas - 1; j > 0; j--)
                if (((*mas) + j - 1)->price > ((*mas) + j)->price)
                    swap_price_keys(((*mas) + j - 1), ((*mas) + j));
        }
        else
        {
            for (int j = 0; j < size_of_mas - 1; j++)
                if (((*mas) + j + 1)->price < ((*mas) + j)->price)
                    swap_price_keys(((*mas) + j + 1), ((*mas) + j));
        }
}

void price_keys_sort_qsort(price_keys *a, int l, int r)
{
    int i = l, j = r;
    float m = a[(l + r) / 2].price;
    do
    {
        for (; a[i].price < m; i++);
        for (; a[j].price > m; j--);
        if (i <= j)
        {
            swap_price_keys(&a[i], &a[j]);
            i++;
            j--;
        }
    }while (i <= j);
    if (l < j)
        price_keys_sort_qsort(a, l, j);
    if (i < r)
        price_keys_sort_qsort(a, i, r);
}

void car_sort_qsort(car *a, int l, int r, int (*comparator)(const car*, const car*))
{
    int i = l, j = r;
    car m = a[(l + r) / 2];
    do
    {
        for (; comparator(&a[i], &m) < 0; i++);
        for (; comparator(&a[j], &m) > 0; j--);
        if (i <= j)
        {
            swap_car_records(&a[i], &a[j]);
            i++;
            j--;
        }
    }while (i <= j);
    if (l < j)
        car_sort_qsort(a, l, j, comparator);
    if (i < r)
        car_sort_qsort(a, i, r, comparator);
}

void car_sort_puz_test(car **mas, int size_of_mas, int (*comparator)(const car*, const car*), int mn)
{
    clock_t start = clock();
    for (int i = 0; i < mn; i++)
    {
        car_sort_puz(mas, size_of_mas, comparator);
    }
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Bubble sort by table test time: %.3f seconds\n", seconds);
}

void price_keys_sort_puz_test(price_keys **mas, int size_of_mas, int mn)
{
    clock_t start = clock();
    for (int i = 0; i < mn; i++)
    {
        price_keys_sort_puz(mas, size_of_mas);
    }
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Bubble sort by keys test time: %.3f seconds\n", seconds);
}

void price_keys_sort_qsort_test(price_keys *a, int l, int r, int mn)
{
    clock_t start = clock();
    for (int i = 0; i < mn; i++)
    {
        price_keys_sort_qsort(a, l, r);
    }
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Quick sort by keys test time: %.3f seconds\n", seconds);
}

void car_sort_qsort_test(car *a, int l, int r, int (*comparator)(const car*, const car*), int mn)
{
    clock_t start = clock();
    for (int i = 0; i < mn; i++)
    {
        car_sort_qsort(a, l, r, comparator);
    }
    clock_t end = clock();
    double seconds = (double)(end - start) / CLOCKS_PER_SEC;
    printf("Quick sort by table test time: %.3f seconds\n", seconds);
}
