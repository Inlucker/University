#include "defines.h"
#include "io_funcs.h"
#include "node_funcs.h"
#include "comporators.h"
#include <stdio.h>
#include <stdlib.h>
#include <check.h>

START_TEST(test_wrong_file)
{
    node_t *test1 = read_file("./unit_files/wrong_file_name.txt");

    int areEqual = 0;

    if (test1 == NULL)
        areEqual = 1;

    ck_assert_int_eq(areEqual, 1);
}
END_TEST

START_TEST(test_sort)
{
    node_t *test = read_file("./unit_files/unit_test_sort.txt");
    //print_infos(test);

    test = sort(test, (int(*)(const void *, const void *)) comp_info);

    //print_infos(test);

    int areEqual = 1;

    node_t *i = test;
    int id = 1;
    while (i != NULL)
    {
        info_t *tmp_data = i->data;
        //printf("%d %d\n", tmp_data->years, id);
        if (tmp_data->years != id)
            areEqual = 0;
        id++;
        i = i->next;
    }

    free_list(&test);
    ck_assert_int_eq(areEqual, 1);
}
END_TEST

START_TEST(test_pop_front)
{
    node_t *test = read_file("./unit_files/unit_test_pop.txt");

    info_t *rez = pop_front(&test);

    int areEqual = 1;

    node_t *i = test;
    int id = 4;
    while (i != NULL)
    {
        info_t *tmp_data = i->data;
        if (tmp_data->years != id)
            areEqual = 0;
        id--;
        i = i->next;
    }

    free_list(&test);
    ck_assert_int_eq(rez->years, 5);
    free(rez);
    ck_assert_int_eq(areEqual, 1);
}
END_TEST

START_TEST(test_pop_back)
{
    node_t *test = read_file("./unit_files/unit_test_pop.txt");

    info_t *rez = pop_back(&test);

    int areEqual = 1;

    node_t *i = test;
    int id = 5;
    while (i != NULL)
    {
        info_t *tmp_data = i->data;
        if (tmp_data->years != id)
            areEqual = 0;
        id--;
        i = i->next;
    }

    free_list(&test);
    ck_assert_int_eq(rez->years, 1);
    free(rez);
    ck_assert_int_eq(areEqual, 1);
}
END_TEST

START_TEST(test_append)
{
    node_t *test1 = read_file("./unit_files/unit_test_append1.txt");
    node_t *test2 = read_file("./unit_files/unit_test_append2.txt");

    append(&test1, &test2);

    int areEqual = 1;

    node_t *i = test1;
    int id = 1;
    while (i != NULL)
    {
        info_t *tmp_data = i->data;
        if (tmp_data->years != id)
            areEqual = 0;
        id++;
        i = i->next;
    }

    free_list(&test1);
    //free_list(&test2);
    ck_assert_int_eq(areEqual, 1);
}
END_TEST

Suite* calc_avg_suite(void)
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
    tcase_add_test(tc_neg, test_wrong_file);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_neg);

    // Создадим тестовый случай из функций-тестов, которые проверяют работу
    // calc_avg для корректных параметров
    tc_pos = tcase_create("positives");
    // Добавим в tc_pos соответствующие функции-тесты
    tcase_add_test(tc_pos, test_sort);
    tcase_add_test(tc_pos, test_pop_front);
    tcase_add_test(tc_pos, test_pop_back);
    tcase_add_test(tc_pos, test_append);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_pos);

    return s;
}

int main()
{

    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = calc_avg_suite();
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
