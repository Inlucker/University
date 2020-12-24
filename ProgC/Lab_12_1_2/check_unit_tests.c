#include <stdio.h>
#include <stdlib.h>
#include <check.h>
#include "mylib.h"

void print_mas(int *mas, int n)
{
    for (int i = 0; i < n; i++)
    {
        printf("%d ", mas[i]);
    }
    printf("\n");
}

START_TEST(test_sdvig)
{
    int n = 4;
    int *mas = malloc(n * sizeof (int));
    for (int i = 0; i < n; i++)
    {
        mas[i] = i + 1;
    }

    //print_mas(mas, n);

    int k = 9122;
    sdvig(mas, n, k);

    //print_mas(mas, n);

    ck_assert_int_eq(mas[0], 3);
    ck_assert_int_eq(mas[1], 4);
    ck_assert_int_eq(mas[2], 1);
    ck_assert_int_eq(mas[3], 2);

    sdvig(mas, n, k);

    ck_assert_int_eq(mas[0], 1);
    ck_assert_int_eq(mas[1], 2);
    ck_assert_int_eq(mas[2], 3);
    ck_assert_int_eq(mas[3], 4);

    free(mas);
}

START_TEST(test_get_new_mas1)
{
    int n = 4;
    int *mas = malloc(n * sizeof (int));
    for (int i = 0; i < n ; i++)
    {
        mas[i] = (i + 1) * (i + 1);
    }

    //print_mas(mas, n);

    int m = 0;
    get_new_mas(mas, n, NULL, &m);

    //print_mas(mas, n);

    int *mas2 = malloc(m * sizeof (int));

    get_new_mas(mas, n, mas2, &m);

    //print_mas(mas2, m);

    ck_assert_int_eq(m, 4);
    ck_assert_int_eq(mas2[0], 1);
    ck_assert_int_eq(mas2[1], 4);
    ck_assert_int_eq(mas2[2], 9);
    ck_assert_int_eq(mas2[3], 16);

    free(mas);
    free(mas2);
}

START_TEST(test_get_new_mas2)
{
    int n = 4;
    int *mas = malloc(n * sizeof (int));
    for (int i = 0; i < n ; i++)
    {
        mas[i] = (i + 1);
    }

    //print_mas(mas, n);

    int m = 0;
    get_new_mas(mas, n, NULL, &m);

    //print_mas(mas, n);

    int *mas2 = malloc(m * sizeof (int));

    get_new_mas(mas, n, mas2, &m);

    //print_mas(mas2, m);

    ck_assert_int_eq(m, 2);
    ck_assert_int_eq(mas2[0], 1);
    ck_assert_int_eq(mas2[1], 4);

    free(mas);
    free(mas2);
}

START_TEST(test_get_new_mas_allocate_max_possible_size1)
{
    int n = 4;
    int *mas = malloc(n * sizeof (int));
    for (int i = 0; i < n ; i++)
    {
        mas[i] = (i + 1) * (i + 1);
    }

    //print_mas(mas, n);

    int m = 5;

    int *mas2 = malloc(m * sizeof (int));

    get_new_mas(mas, n, mas2, &m);

    print_mas(mas2, m);

    ck_assert_int_eq(m, 4);
    ck_assert_int_eq(mas2[0], 1);
    ck_assert_int_eq(mas2[1], 4);
    ck_assert_int_eq(mas2[2], 9);
    ck_assert_int_eq(mas2[3], 16);

    free(mas);
    free(mas2);
}

START_TEST(test_get_new_mas_allocate_max_possible_size2)
{
    int n = 4;
    int *mas = malloc(n * sizeof (int));
    for (int i = 0; i < n ; i++)
    {
        mas[i] = (i + 1);
    }

    //print_mas(mas, n);

    int m = 5;

    int *mas2 = malloc(m * sizeof (int));

    get_new_mas(mas, n, mas2, &m);

    print_mas(mas2, m);

    ck_assert_int_eq(m, 2);
    ck_assert_int_eq(mas2[0], 1);
    ck_assert_int_eq(mas2[1], 4);

    free(mas);
    free(mas2);
}

Suite* my_lib_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    // Создадим тестовый набор для тестирования функции calc_avg
    s = suite_create("mysort");

    // Создадим тестовый случай из функций-тестов, которые проверяют разного
    // рода ошибочные ситуации при вызове calc_avg
    tc_neg = tcase_create("negatives");
    // Добавим в tc_neg соответствующие функции-тесты
    //tcase_add_test(tc_neg, test_key_input_same_ptrs);
    //tcase_add_test(tc_neg, test_key_input_zero_elems_after_key);
    //tcase_add_test(tc_neg, test_key_input_wrong_data);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_neg);

    // Создадим тестовый случай из функций-тестов, которые проверяют работу
    // calc_avg для корректных параметров
    tc_pos = tcase_create("positives");
    // Добавим в tc_pos соответствующие функции-тесты
    tcase_add_test(tc_pos, test_sdvig);
    tcase_add_test(tc_pos, test_get_new_mas1);
    tcase_add_test(tc_pos, test_get_new_mas2);
    tcase_add_test(tc_pos, test_get_new_mas_allocate_max_possible_size1);
    tcase_add_test(tc_pos, test_get_new_mas_allocate_max_possible_size2);
    //tcase_add_test(tc_pos, test_mysort);
    //tcase_add_test(tc_pos, test_key);
    //tcase_add_test(tc_pos, test_mysort_chars);
    //tcase_add_test(tc_pos, test_mysort_doubles);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_pos);

    return s;
}

int main()
{

    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = my_lib_suite();
    // Для запуска тестов, всходящих в тестовый набор, нужно создать так называемый
    // "runner".
    runner = srunner_create(s);

    // Вот таким образом запускаются все тесты. С помощью второго параметра (в данном случаев
    // CK_VERBOSE) можно детализировать вывод.
    srunner_run_all(runner, CK_VERBOSE);
    // После того, как все тесты будут выполнены, можно получить по ним дополнительную информацию,
    // например, вот так.
    no_failed = srunner_ntests_failed(runner);
    // Перед завершением main "runner" нужно обязательно освободить.
    srunner_free(runner);

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;

    /*int count = mysort_test();
    printf("Errors count: %d", count);*/

    //return 0;
}
