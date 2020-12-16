#include "defines.h"
#include "my_snprintf.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <check.h>

START_TEST(test_buf_size_equals_count)
{
    char buf[10] = "lol";
    char *s = "XD LOL KEK";

    int rez1 = my_snprintf(buf, strlen(s), "%s", s);

    //printf("%s; %d\n", buf, rez1);

    char *buf1 = NULL;
    buf1 = malloc(20);
    sprintf(buf1, "%s", buf);

    snprintf(buf, 3, "%s", "lol");
    int rez2 = snprintf(buf, strlen(s), "%s", s);

    //printf("%s; %d\n", buf, rez2);

    char *buf2 = NULL;
    buf2 = malloc(20);
    sprintf(buf2, "%s", buf);

    //printf("%s; %d\n", buf1, rez1);
    //printf("%s; %d\n", buf2, rez2);

    ck_assert_int_eq(rez1, rez2);
    ck_assert_str_eq(buf1, buf2);

    free(buf1);
    free(buf2);
}
END_TEST

START_TEST(test_buf_size_more_than_count)
{
    char buf[11] = "lol";
    char *s = "XD LOL KEK";

    int rez1 = my_snprintf(buf, 5, "%s", s);

    //printf("%s; %d\n", buf, rez1);

    char *buf1 = NULL;
    buf1 = malloc(20);
    sprintf(buf1, "%s", buf);

    snprintf(buf, 3, "%s", "lol");
    int rez2 = snprintf(buf, 5, "%s", s);

    //printf("%s; %d\n", buf, rez2);

    char *buf2 = NULL;
    buf2 = malloc(20);
    sprintf(buf2, "%s", buf);

    //printf("%s; %d\n", buf1, rez1);
    //printf("%s; %d\n", buf2, rez2);

    ck_assert_int_eq(rez1, rez2);
    ck_assert_str_eq(buf1, buf2);

    free(buf1);
    free(buf2);
}
END_TEST

START_TEST(test_wrong_format)
{
    char buf[11] = "lol";
    char *s = "XD LOL KEK";

    int rez1 = my_snprintf(buf, 5, "%{s", s);

    //printf("%s; %d\n", buf, rez1);

    char *buf1 = NULL;
    buf1 = malloc(20);
    sprintf(buf1, "%s", buf);

    //int rez2 = snprintf(buf, 5, "%d");

    //printf("%s; %d\n", buf, rez2);

    /*char *buf2 = NULL;
    buf2 = malloc(20);
    sprintf(buf2, "%s", buf);*/

    //printf("%s; %d\n", buf1, rez1);
    //printf("%s; %d\n", buf2, rez2);

    ck_assert_int_eq(rez1, 2);
    ck_assert_str_eq(buf1, "{s");

    free(buf1);
    //free(buf2);
}
END_TEST

START_TEST(test_count_equals_zero_but_s_is_not_empty)
{
    char buf[11] = "lol";
    char *s = "XD LOL KEK";

    int rez1 = my_snprintf(buf, 0, "%s", s);

    //printf("%s; %d\n", buf, rez1);

    char *buf1 = NULL;
    buf1 = malloc(20);
    sprintf(buf1, "%s", buf);

    snprintf(buf, 3, "%s", "lol");
    int rez2 = snprintf(buf, 0, "%s", s);

    //printf("%s; %d\n", buf, rez2);

    char *buf2 = NULL;
    buf2 = malloc(20);
    sprintf(buf2, "%s", buf);

    //printf("%s; %d\n", buf1, rez1);
    //printf("%s; %d\n", buf2, rez2);

    ck_assert_int_eq(rez1, rez2);
    ck_assert_str_eq(buf1, buf2);

    free(buf1);
    free(buf2);
}
END_TEST

START_TEST(test_double_argument)
{
    char buf[20] = "lol";
    char *s = "XD LOL KEK";
    char *s2 = "CHEBUREK";

    int rez1 = my_snprintf(buf, 20, "%s %s", s, s2);

    //printf("%s; %d\n", buf, rez1);

    char *buf1 = NULL;
    buf1 = malloc(20);
    sprintf(buf1, "%s", buf);

    snprintf(buf, 3, "%s", "lol");
    int rez2 = snprintf(buf, 20, "%s %s", s, s2);

    //printf("%s; %d\n", buf, rez2);

    char *buf2 = NULL;
    buf2 = malloc(20);
    sprintf(buf2, "%s", buf);

    //printf("%s; %d\n", buf1, rez1);
    //printf("%s; %d\n", buf2, rez2);

    ck_assert_int_eq(rez1, rez2);
    ck_assert_str_eq(buf1, buf2);

    free(buf1);
    free(buf2);
}
END_TEST

START_TEST(test_buf_size_equals_count_plus_one)
{
    char buf[11] = "lol";
    char *s = "XD LOL KEK";

    int rez1 = my_snprintf(buf, strlen(s), "%s", s);

    //printf("%s; %d\n", buf, rez1);

    char *buf1 = NULL;
    buf1 = malloc(20);
    sprintf(buf1, "%s", buf);

    snprintf(buf, 3, "%s", "lol");
    int rez2 = snprintf(buf, strlen(s), "%s", s);

    //printf("%s; %d\n", buf, rez2);

    char *buf2 = NULL;
    buf2 = malloc(20);
    sprintf(buf2, "%s", buf);

    //printf("%s; %d\n", buf1, rez1);
    //printf("%s; %d\n", buf2, rez2);

    ck_assert_int_eq(rez1, rez2);
    ck_assert_str_eq(buf1, buf2);

    free(buf1);
    free(buf2);
}
END_TEST

START_TEST(test_count_equals_zero)
{
    char buf[11] = "lol";
    char *s = "";

    int rez1 = my_snprintf(buf, 0, "%s", s);

    //printf("%s; %d\n", buf, rez1);

    char *buf1 = NULL;
    buf1 = malloc(20);
    sprintf(buf1, "%s", buf);

    snprintf(buf, 3, "%s", "lol");
    int rez2 = snprintf(buf, 0, "%s", s);

    //printf("%s; %d\n", buf, rez2);

    char *buf2 = NULL;
    buf2 = malloc(20);
    sprintf(buf2, "%s", buf);

    //printf("%s; %d\n", buf1, rez1);
    //printf("%s; %d\n", buf2, rez2);

    ck_assert_int_eq(rez1, rez2);
    ck_assert_str_eq(buf1, buf2);

    free(buf1);
    free(buf2);
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
    tcase_add_test(tc_neg, test_buf_size_equals_count);
    tcase_add_test(tc_neg, test_buf_size_more_than_count);
    tcase_add_test(tc_neg, test_wrong_format);
    tcase_add_test(tc_neg, test_count_equals_zero_but_s_is_not_empty);
    tcase_add_test(tc_neg, test_double_argument);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_neg);

    // Создадим тестовый случай из функций-тестов, которые проверяют работу
    // calc_avg для корректных параметров
    tc_pos = tcase_create("positives");
    // Добавим в tc_pos соответствующие функции-тесты
    tcase_add_test(tc_pos, test_buf_size_equals_count_plus_one);
    tcase_add_test(tc_pos, test_count_equals_zero);

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
