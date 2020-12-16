#include "defines.h"
#include "io_funcs.h"
#include "node_funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <check.h>

START_TEST(test_wrong_file)
{
    list_t *test1 = read_file("./files_for_unit_tests/test_wrong_file_name.txt");

    int areEqual = 0;

    if (test1 == NULL)
        areEqual = 1;

    ck_assert_int_eq(areEqual, 1);
}
END_TEST

START_TEST(test_wrong_input)
{
    list_t *test1 = read_file("./files_for_unit_tests/wrong_input.txt");

    int areEqual = 0;

    if (test1 == NULL)
        areEqual = 1;

    ck_assert_int_eq(areEqual, 1);
}
END_TEST

START_TEST(test_addition)
{
    list_t *list1 = read_file("./files_for_unit_tests/test1.txt");
    list_t *list2 = read_file("./files_for_unit_tests/test2.txt");
    list_t *rez = addition(list1, list2);

    int areEqual = 1;

    node_t *i = rez->head;
    int id = 1;
    while (i != NULL)
    {
        if (i->data->value != id * 2)
            areEqual = 0;
        id++;
        i = i->next;
    }

    free_list(&list1);
    free_list(&list2);
    ck_assert_int_eq(areEqual, 1);
}
END_TEST

START_TEST(test_composition)
{
    list_t *list1 = read_file("./files_for_unit_tests/test3.txt");
    list_t *list2 = read_file("./files_for_unit_tests/test4.txt");
    list_t *rez = compostion(list1, list2);

    int areEqual = 1;

    node_t *i = rez->head;

    if (i->data->value != 1)
        areEqual = 0;
    i = i->next;

    if (i->data->value != 8)
        areEqual = 0;
    i = i->next;

    if (i->data->value != 1)
        areEqual = 0;
    i = i->next;

    if (i->data->value != -9)
        areEqual = 0;
    i = i->next;

    if (i->data->value != 24)
        areEqual = 0;
    i = i->next;

    if (i->data->value != -15)
        areEqual = 0;
    i = i->next;

    if (i->data->value != 15)
        areEqual = 0;
    i = i->next;

    if (i->data->value != 31)
        areEqual = 0;
    i = i->next;

    if (i->data->value != 26)
        areEqual = 0;
    i = i->next;

    free_list(&list1);
    free_list(&list2);
    ck_assert_int_eq(areEqual, 1);
}
END_TEST

START_TEST(test_line_deletion)
{
    list_t *list1 = read_file("./files_for_unit_tests/test5.txt");
    list_t *list2 = read_file("./files_for_unit_tests/test6.txt");
    delete_max_line(list1);
    delete_max_line(list2);

    //print_list(list1);
    //print_list(list2);

    int areEqual = 1;

    node_t *i = list1->head;
    int id = 1;
    while (i != NULL)
    {
        if (i->data->value != id)
            areEqual = 0;
        id++;
        i = i->next;
    }

    i = list2->head;
    id = 4;
    while (i != NULL)
    {
        if (i->data->value != id)
            areEqual = 0;
        id++;
        i = i->next;
    }

    free_list(&list1);
    free_list(&list2);
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
    tcase_add_test(tc_neg, test_wrong_input);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_neg);

    // Создадим тестовый случай из функций-тестов, которые проверяют работу
    // calc_avg для корректных параметров
    tc_pos = tcase_create("positives");
    // Добавим в tc_pos соответствующие функции-тесты
    tcase_add_test(tc_pos, test_addition);
    tcase_add_test(tc_pos, test_composition);
    tcase_add_test(tc_pos, test_line_deletion);

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
