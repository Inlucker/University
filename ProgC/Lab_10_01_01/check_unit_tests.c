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

    ck_assert_ptr_eq(test1, NULL);
}
END_TEST

START_TEST(test_sort_usual)
{
    node_t *test = read_file("./unit_files/unit_test_sort.txt");
    //print_infos(test);

    test = sort(test, (int(*)(const void *, const void *)) comp_info);

    //print_infos(test);

    //int areEqual = 1;

    node_t *i = test;
    char id = 'A';
    while (i != NULL)
    {
        info_t *tmp_data = i->data;
        //printf("%d %d\n", tmp_data->years, id);
        ck_assert_int_eq(tmp_data->name[0], id);
        /*if (tmp_data->name[0] != id)
            areEqual = 0;*/
        id++;
        i = i->next;
    }

    //ck_assert_int_eq(areEqual, 1);
    free_list(&test);
}
END_TEST

START_TEST(test_sort_same_names)
{
    node_t *test = read_file("./unit_files/unit_test_sort2.txt");
    //print_infos(test);

    test = sort(test, (int(*)(const void *, const void *)) comp_info);

    //print_infos(test);

    //int areEqual = 1;

    node_t *i = test;
    int id = 1;
    while (i != NULL)
    {
        info_t *tmp_data = i->data;
        //printf("%d %d\n", tmp_data->years, id);
        ck_assert_int_eq(tmp_data->years, id);
        /*if (tmp_data->years != id)
            areEqual = 0;*/
        id++;
        i = i->next;
    }

    //ck_assert_int_eq(areEqual, 1);
    free_list(&test);
}
END_TEST

START_TEST(test_sort_same_names_and_years)
{
    node_t *test = read_file("./unit_files/unit_test_sort3.txt");
    //print_infos(test);

    test = sort(test, (int(*)(const void *, const void *)) comp_info);

    //print_infos(test);

    //int areEqual = 1;

    node_t *i = test;
    double id = 1.4;
    while (i != NULL)
    {
        info_t *tmp_data = i->data;
        //printf("%d %d\n", tmp_data->years, id);
        ck_assert_double_eq(tmp_data->intelect, id);
        /*if (tmp_data->intelect != id)
            areEqual = 0;*/
        id++;
        i = i->next;
    }

    //ck_assert_int_eq(areEqual, 1);
    free_list(&test);
}
END_TEST

START_TEST(test_sort_same_name_start)
{
    node_t *test = read_file("./unit_files/unit_test_sort4.txt");
    //print_infos(test);

    test = sort(test, (int(*)(const void *, const void *)) comp_info);

    //print_infos(test);

    //int areEqual = 1;

    node_t *i = test;

    info_t *tmp_data = i->data;
    ck_assert_str_eq(tmp_data->name, "Arsenz");
    i = i->next;

    tmp_data = i->data;
    ck_assert_str_eq(tmp_data->name, "Arsenzz");
    i = i->next;

    tmp_data = i->data;
    ck_assert_str_eq(tmp_data->name, "Arsezz");
    i = i->next;

    tmp_data = i->data;
    ck_assert_str_eq(tmp_data->name, "Arszzz");
    i = i->next;

    tmp_data = i->data;
    ck_assert_str_eq(tmp_data->name, "Arzzzz");
    i = i->next;

    ck_assert_ptr_eq(i, NULL);
    free_list(&test);
}
END_TEST

START_TEST(test_sort_empty_list)
{
    node_t *test = read_file("./unit_files/unit_test_empty_list.txt");
    //print_infos(test);

    test = sort(test, (int(*)(const void *, const void *)) comp_info);

    //print_infos(test);

    ck_assert_ptr_eq(test, NULL);
    free_list(&test);
}
END_TEST

START_TEST(test_pop_front_usual)
{
    node_t *test = read_file("./unit_files/unit_test_pop1.txt");

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

    ck_assert_str_eq(rez->name, "Sokolov");
    //ck_assert_int_eq(rez->name[0], 'S');
    ck_assert_int_eq(rez->years, 5);
    ck_assert_double_eq(rez->intelect, 5.4);
    ck_assert_int_eq(areEqual, 1);
    free(rez);
    free_list(&test);
}
END_TEST

START_TEST(test_pop_front_last_element)
{
    node_t *test = read_file("./unit_files/unit_test_pop2.txt");

    info_t *rez = pop_front(&test);

    ck_assert_str_eq(rez->name, "Ivanov");
    //ck_assert_int_eq(rez->name[0], 'I');
    ck_assert_int_eq(rez->years, 1);
    ck_assert_double_eq(rez->intelect, 2.0);
    ck_assert_ptr_eq(test, NULL);
    free_list(&test);
    free(rez);
}
END_TEST

START_TEST(test_pop_front_empty_list)
{
    node_t *test = read_file("./unit_files/unit_test_empty_file.txt");

    info_t *rez = pop_front(&test);

    ck_assert_ptr_eq(rez, NULL);
    ck_assert_ptr_eq(test, NULL);
    free_list(&test);
    free(rez);
}
END_TEST

START_TEST(test_pop_back_usual)
{
    node_t *test = read_file("./unit_files/unit_test_pop1.txt");

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

    ck_assert_str_eq(rez->name, "Ivanov");
    //ck_assert_int_eq(rez->name[0], 'I');
    ck_assert_int_eq(rez->years, 1);
    ck_assert_double_eq(rez->intelect, 2.0);
    ck_assert_int_eq(areEqual, 1);
    free(rez);
    free_list(&test);
}
END_TEST

START_TEST(test_pop_back_last_element)
{
    node_t *test = read_file("./unit_files/unit_test_pop2.txt");

    info_t *rez = pop_back(&test);

    ck_assert_str_eq(rez->name, "Ivanov");
    //ck_assert_int_eq(rez->name[0], 'I');
    ck_assert_int_eq(rez->years, 1);
    ck_assert_double_eq(rez->intelect, 2.0);
    ck_assert_ptr_eq(test, NULL);
    free(rez);
    free_list(&test);
}
END_TEST

START_TEST(test_pop_back_empty_list)
{
    node_t *test = read_file("./unit_files/unit_test_empty_file.txt");

    info_t *rez = pop_back(&test);

    ck_assert_ptr_eq(rez, NULL);
    ck_assert_ptr_eq(test, NULL);
    free(rez);
    free_list(&test);
}
END_TEST

START_TEST(test_append_usual)
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

    //print_infos(test1);

    ck_assert_int_eq(areEqual, 1);
    ck_assert_ptr_eq(test2, NULL);
    free_list(&test1);
    free_list(&test2);
}
END_TEST

START_TEST(test_append_null_ptr_to_usual_list)
{
    node_t *test1 = read_file("./unit_files/unit_test_append1.txt");
    node_t *test2 = read_file("./unit_files/unit_test_empty_file.txt");

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

    //print_infos(test1);

    ck_assert_int_eq(areEqual, 1);
    ck_assert_ptr_eq(test2, NULL);
    free_list(&test1);
    free_list(&test2);
}
END_TEST

START_TEST(test_append_usual_list_to_null_ptr)
{
    node_t *test1 = read_file("./unit_files/unit_test_empty_file.txt");
    node_t *test2 = read_file("./unit_files/unit_test_append1.txt");

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

    //print_infos(test1);

    ck_assert_int_eq(areEqual, 1);
    ck_assert_ptr_eq(test2, NULL);
    free_list(&test1);
    free_list(&test2);
}
END_TEST

START_TEST(test_append_null_ptr_to_null_ptr)
{
    node_t *test1 = read_file("./unit_files/unit_test_empty_file.txt");
    node_t *test2 = read_file("./unit_files/unit_test_empty_file.txt");

    append(&test1, &test2);

    ck_assert_ptr_eq(test1, NULL);
    ck_assert_ptr_eq(test2, NULL);
    free_list(&test1);
    free_list(&test2);
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

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_neg);

    // Создадим тестовый случай для позитивных тестов
    tc_pos = tcase_create("positives");
    // Добавим в tc_pos соответствующие функции-тесты
    tcase_add_test(tc_pos, test_sort_usual);
    tcase_add_test(tc_pos, test_sort_same_names);
    tcase_add_test(tc_pos, test_sort_same_names_and_years);
    tcase_add_test(tc_pos, test_sort_same_name_start);
    tcase_add_test(tc_pos, test_sort_empty_list);

    tcase_add_test(tc_pos, test_pop_front_usual);
    tcase_add_test(tc_pos, test_pop_front_last_element);
    tcase_add_test(tc_pos, test_pop_front_empty_list);

    tcase_add_test(tc_pos, test_pop_back_usual);
    tcase_add_test(tc_pos, test_pop_back_last_element);
    tcase_add_test(tc_pos, test_pop_back_empty_list);

    tcase_add_test(tc_pos, test_append_usual);
    tcase_add_test(tc_pos, test_append_null_ptr_to_usual_list);
    tcase_add_test(tc_pos, test_append_usual_list_to_null_ptr);
    tcase_add_test(tc_pos, test_append_null_ptr_to_null_ptr);

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
