#include "defines.h"
#include "io_funcs.h"
#include "node_funcs.h"
#include <stdio.h>
#include <stdlib.h>
#include <check.h>

START_TEST(test_wrong_file)
{
    list_t *test1 = read_file("./files_for_unit_tests/test_wrong_file_name.txt");

    ck_assert_ptr_eq(test1, NULL);
}
END_TEST

START_TEST(test_wrong_input)
{
    list_t *test1 = read_file("./files_for_unit_tests/wrong_input.txt");

    ck_assert_ptr_eq(test1, NULL);
}
END_TEST

START_TEST(test_addition_null_ptr)
{
    list_t *list1 = read_file("./files_for_unit_tests/no_such_file.txt");
    list_t *list2 = read_file("./files_for_unit_tests/test2.txt");
    list_t *rez = addition(list1, list2);

    ck_assert_ptr_eq(rez, NULL);
    free_list(&list1);
    free_list(&list2);
    free_list(&rez);
}
END_TEST

START_TEST(test_composition_null_ptr)
{
    list_t *list1 = read_file("./files_for_unit_tests/no_such_file.txt");
    list_t *list2 = read_file("./files_for_unit_tests/test2.txt");
    list_t *rez = compostion(list1, list2);

    ck_assert_ptr_eq(rez, NULL);
    free_list(&list1);
    free_list(&list2);
    free_list(&rez);
}
END_TEST

START_TEST(test_line_deletion_null_ptr)
{
    list_t *list1 = read_file("./files_for_unit_tests/no_such_file.txt");
    list_t *list2 = read_file("./files_for_unit_tests/no_such_file.txt");
    delete_max_line(list1);
    delete_max_line(list2);

    ck_assert_ptr_eq(list1, NULL);
    ck_assert_ptr_eq(list2, NULL);
    free_list(&list1);
    free_list(&list2);
}
END_TEST

START_TEST(test_addition_usual)
{
    list_t *list1 = read_file("./files_for_unit_tests/test1.txt");
    list_t *list2 = read_file("./files_for_unit_tests/test2.txt");
    list_t *rez = addition(list1, list2);

    //int areEqual = 1;

    node_t *i = rez->head;
    int id = 1;
    while (i != NULL)
    {
        ck_assert_int_eq(i->data->value, id * 2);
        /*if (i->data->value != id * 2)
            areEqual = 0;*/
        id++;
        i = i->next;
    }

    //ck_assert_int_eq(areEqual, 1);
    free_list(&list1);
    free_list(&list2);
    free_list(&rez);
}
END_TEST

START_TEST(test_addition_add_zero)
{
    list_t *list1 = read_file("./files_for_unit_tests/test1.txt");
    list_t *list2 = read_file("./files_for_unit_tests/test3(zero).txt");
    //print_list(list1);
    //print_list(list2);
    list_t *rez = addition(list1, list2);
    //print_list(rez);

    //int areEqual = 1;

    node_t *i = rez->head;

    ck_assert_int_eq(i->data->value, 1);
    i = i->next;

    ck_assert_int_eq(i->data->value, 6);
    i = i->next;

    ck_assert_int_eq(i->data->value, 8);
    i = i->next;


    ck_assert_ptr_eq(i, NULL);
    free_list(&list1);
    free_list(&list2);
    free_list(&rez);
}
END_TEST

START_TEST(test_addition_rez_eq_zero)
{
    list_t *list1 = read_file("./files_for_unit_tests/test1.txt");
    list_t *list2 = read_file("./files_for_unit_tests/test1(neg).txt");
    list_t *rez = addition(list1, list2);

    ck_assert_ptr_eq(rez, NULL);
    free_list(&list1);
    free_list(&list2);
    free_list(&rez);
}
END_TEST

START_TEST(test_composition_usual)
{
    list_t *list1 = read_file("./files_for_unit_tests/test3.txt");
    list_t *list2 = read_file("./files_for_unit_tests/test4.txt");
    list_t *rez = compostion(list1, list2);

    //int areEqual = 1;

    node_t *i = rez->head;

    /*if (i->data->value != 1)
        areEqual = 0;*/
    ck_assert_int_eq(i->data->value, 1);
    i = i->next;

    /*if (i->data->value != 8)
        areEqual = 0;*/
    ck_assert_int_eq(i->data->value, 8);
    i = i->next;

    /*if (i->data->value != 1)
        areEqual = 0;*/
    ck_assert_int_eq(i->data->value, 1);
    i = i->next;

    /*if (i->data->value != -9)
        areEqual = 0;*/
    ck_assert_int_eq(i->data->value, -9);
    i = i->next;

    /*if (i->data->value != 24)
        areEqual = 0;*/
    ck_assert_int_eq(i->data->value, 24);
    i = i->next;

    /*if (i->data->value != -15)
        areEqual = 0;*/
    ck_assert_int_eq(i->data->value, -15);
    i = i->next;

    /*if (i->data->value != 15)
        areEqual = 0;*/
    ck_assert_int_eq(i->data->value, 15);
    i = i->next;

    /*if (i->data->value != 31)
        areEqual = 0;*/
    ck_assert_int_eq(i->data->value, 31);
    i = i->next;

    /*if (i->data->value != 26)
        areEqual = 0;*/
    ck_assert_int_eq(i->data->value, 26);
    i = i->next;

    //ck_assert_int_eq(areEqual, 1);
    free_list(&list1);
    free_list(&list2);
    free_list(&rez);
}
END_TEST

START_TEST(test_composition_rez_eq_zero)
{
    list_t *list1 = read_file("./files_for_unit_tests/test3.txt");
    list_t *list2 = read_file("./files_for_unit_tests/test3(zero).txt");
    list_t *rez = compostion(list1, list2);

    ck_assert_ptr_eq(rez->head, NULL);
    ck_assert_ptr_eq(rez->tail, NULL);
    free_list(&list1);
    free_list(&list2);
    free_list(&rez);
}
END_TEST

START_TEST(test_composition_on_one)
{
    list_t *list1 = read_file("./files_for_unit_tests/test3.txt");
    list_t *list2 = read_file("./files_for_unit_tests/test4(one).txt");
    list_t *rez = compostion(list1, list2);

    //int areEqual = 1;

    node_t *i = rez->head;

    ck_assert_int_eq(i->data->value, 1);
    i = i->next;

    ck_assert_int_eq(i->data->value, 3);
    i = i->next;

    ck_assert_int_eq(i->data->value, -2);
    i = i->next;

    ck_assert_int_eq(i->data->value, 3);
    i = i->next;

    ck_assert_int_eq(i->data->value, 2);
    i = i->next;

    ck_assert_int_eq(i->data->value, 1);
    i = i->next;

    //ck_assert_int_eq(areEqual, 1);
    free_list(&list1);
    free_list(&list2);
    free_list(&rez);
}
END_TEST

START_TEST(test_line_deletion_usual)
{
    list_t *list1 = read_file("./files_for_unit_tests/test567.txt");
    delete_max_line(list1);

    //print_list(list1);
    //print_list(list2);

    //int areEqual = 1;

    node_t *i = list1->head;
    int id = 1;
    while (i != NULL)
    {
        ck_assert_int_eq(i->data->value, id);
        id++;
        i = i->next;
    }

    //ck_assert_int_eq(areEqual, 1);
    free_list(&list1);
}
END_TEST

START_TEST(test_line_deletion_last_line)
{
    list_t *list1 = read_file("./files_for_unit_tests/test5.txt");
    delete_max_line(list1);

    node_t *i = list1->head;
    int id = 1;
    while (i != NULL)
    {
        ck_assert_int_eq(i->data->value, id);
        id++;
        i = i->next;
    }

    free_list(&list1);
}
END_TEST

START_TEST(test_line_deletion_first_line)
{
    list_t *list2 = read_file("./files_for_unit_tests/test6.txt");
    delete_max_line(list2);

    node_t *i = list2->head;
    int id = 4;
    while (i != NULL)
    {
        ck_assert_int_eq(i->data->value, id);
        id++;
        i = i->next;
    }

    free_list(&list2);
}
END_TEST

START_TEST(test_line_deletion_only_one_line)
{
    list_t *list1 = read_file("./files_for_unit_tests/test7.txt");
    delete_max_line(list1);

    ck_assert_ptr_eq(list1->head, NULL);
    ck_assert_ptr_eq(list1->tail, NULL);
    free_list(&list1);
}
END_TEST

Suite* node_funcs_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    // Создадим тестовый набор для тестирования функций
    s = suite_create("node_funcs");

    // Создадим тестовый случай для негативных тестов
    tc_neg = tcase_create("negatives");
    // Добавим в tc_neg соответствующие функции-тесты
    tcase_add_test(tc_neg, test_wrong_file);
    tcase_add_test(tc_neg, test_wrong_input);
    tcase_add_test(tc_neg, test_addition_null_ptr);
    tcase_add_test(tc_neg, test_composition_null_ptr);
    tcase_add_test(tc_neg, test_line_deletion_null_ptr);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_neg);

    // Создадим тестовый случай для позитивных тестов
    tc_pos = tcase_create("positives");
    // Добавим в tc_pos соответствующие функции-тесты
    tcase_add_test(tc_pos, test_addition_usual);
    tcase_add_test(tc_pos, test_addition_rez_eq_zero);
    tcase_add_test(tc_pos, test_addition_add_zero);

    tcase_add_test(tc_pos, test_composition_usual);
    tcase_add_test(tc_pos, test_composition_rez_eq_zero);
    tcase_add_test(tc_pos, test_composition_on_one);

    tcase_add_test(tc_pos, test_line_deletion_usual);
    tcase_add_test(tc_pos, test_line_deletion_last_line);
    tcase_add_test(tc_pos, test_line_deletion_first_line);
    tcase_add_test(tc_pos, test_line_deletion_only_one_line);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_pos);

    return s;
}

int main()
{
    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = node_funcs_suite();
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
}
