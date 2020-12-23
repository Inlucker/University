#include "defines.h"
#include "my_snprintf.h"
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <check.h>

#define EXIT_FAIL 0;

START_TEST(test_wrong_format)
{
    char buf[11] = "lol";
    char *s = "XD LOL KEK";

    int rez1 = my_snprintf(buf, 5, "%{s", s);

    ck_assert_int_eq(rez1, 2);
    ck_assert_str_eq(buf, "{s");
}
END_TEST

START_TEST(test_buf_size_equals_count_s)
{
    char buf[10] = "lol";
    char *s = "XD LOL KEK";

    int rez1 = my_snprintf(buf, strlen(s), "%s", s);

    //printf("%s; %d\n", buf, rez1);

    char *buf1 = NULL;
    buf1 = malloc(20);
    sprintf(buf1, "%s", buf);

    snprintf(buf, 4, "%s", "lol");
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

START_TEST(test_buf_size_more_than_count_s)
{
    char buf[11] = "lol";
    char *s = "XD LOL KEK";

    int rez1 = my_snprintf(buf, 5, "%s", s);

    //printf("%s; %d\n", buf, rez1);

    char *buf1 = NULL;
    buf1 = malloc(20);
    sprintf(buf1, "%s", buf);

    snprintf(buf, 4, "%s", "lol");
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

START_TEST(test_count_equals_zero_but_s_is_not_empty_s)
{
    char buf[11] = "lol";
    char *s = "XD LOL KEK";

    int rez1 = my_snprintf(buf, 0, "%s", s);

    //printf("%s; %d\n", buf, rez1);

    char *buf1 = NULL;
    buf1 = malloc(20);
    sprintf(buf1, "%s", buf);

    snprintf(buf, 4, "%s", "lol");
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

START_TEST(test_double_argument_s)
{
    char buf[20] = "lol";
    char *s = "XD LOL KEK";
    char *s2 = "CHEBUREK";

    int rez1 = my_snprintf(buf, 20, "%s %s", s, s2);

    //printf("%s; %d\n", buf, rez1);

    char *buf1 = NULL;
    buf1 = malloc(20);
    sprintf(buf1, "%s", buf);

    snprintf(buf, 4, "%s", "lol");
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

START_TEST(test_buf_size_equals_count_ho)
{
    //printf("test_buf_size_equals_count_ho\n");
    char buf[10] = "lol";
    int n = -123;

    int rez1 = my_snprintf(buf, 6, "%ho", n); //my_snprintf

    //printf("%s; %d\n", buf, rez1);

    char *buf1 = NULL;
    buf1 = malloc(20);
    sprintf(buf1, "%s", buf);

    snprintf(buf, 4, "%s", "lol");
    int rez2 = snprintf(buf, 6, "%ho", n);

    //printf("%s; %d\n", buf, rez2);

    char *buf2 = NULL;
    buf2 = malloc(20);
    sprintf(buf2, "%s", buf);

    ck_assert_int_eq(rez1, rez2);
    ck_assert_str_eq(buf1, buf2);

    free(buf1);
    free(buf2);
}
END_TEST

START_TEST(test_buf_size_more_than_count_ho)
{
    //printf("test_buf_size_more_than_count_ho\n");
    char buf[11] = "lol";
    int n = -123;

    int rez1 = my_snprintf(buf, 3, "%ho", n); //my_snprintf

    //printf("%s; %d\n", buf, rez1);

    char *buf1 = NULL;
    buf1 = malloc(20);
    sprintf(buf1, "%s", buf);

    snprintf(buf, 4, "%s", "lol");
    int rez2 = snprintf(buf, 3, "%ho", n);

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

START_TEST(test_count_equals_zero_but_s_is_not_empty_ho)
{
    //printf("test_count_equals_zero_but_s_is_not_empty_ho\n");
    char buf[11] = "lol";
    int n = -123;

    int rez1 = my_snprintf(buf, 0, "%ho", n); //my_snprintf

    //printf("%s; %d\n", buf, rez1);

    char *buf1 = NULL;
    buf1 = malloc(20);
    sprintf(buf1, "%s", buf);

    snprintf(buf, 4, "%s", "lol");
    int rez2 = snprintf(buf, 0, "%ho", n);

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

START_TEST(test_double_argument_ho)
{
    //printf("test_double_argument_ho\n");
    char buf[20] = "lol";
    int n = -123;
    int n2 = 123;

    int rez1 = my_snprintf(buf, 20, "%ho %ho", n, n2); //my_snprintf

    //printf("%s; %d\n", buf, rez1);

    char *buf1 = NULL;
    buf1 = malloc(20);
    sprintf(buf1, "%s", buf);

    snprintf(buf, 4, "%s", "lol");
    int rez2 = snprintf(buf, 20, "%ho %ho", n, n2);

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

START_TEST(test_buf_size_equals_count_plus_one_s)
{
    char buf[11] = "lol";
    char *s = "XD LOL KEK";

    int rez1 = my_snprintf(buf, strlen(s) + 1, "%s", s);

    //printf("%s; %d\n", buf, rez1);

    char *buf1 = NULL;
    buf1 = malloc(20);
    sprintf(buf1, "%s", buf);

    snprintf(buf, 4, "%s", "lol");
    int rez2 = snprintf(buf, strlen(s) + 1, "%s", s);

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

START_TEST(test_count_equals_zero_s)
{
    char buf[11] = "lol";
    char *s = "";

    int rez1 = my_snprintf(buf, 0, "%s", s);

    //printf("%s; %d\n", buf, rez1);

    char *buf1 = NULL;
    buf1 = malloc(20);
    sprintf(buf1, "%s", buf);

    snprintf(buf, 4, "%s", "lol");
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

START_TEST(test_buf_size_equals_count_plus_one_ho)
{
    //printf("test_buf_size_equals_count_plus_one_ho\n");
    char buf[11] = "lol";
    int n = -123;

    int rez1 = my_snprintf(buf, 7, "%ho", n); //my_snprintf

    //printf("%s; %d\n", buf, rez1);

    char *buf1 = NULL;
    buf1 = malloc(20);
    sprintf(buf1, "%s", buf);

    snprintf(buf, 4, "%s", "lol");
    int rez2 = snprintf(buf, 7, "%ho", n);

    //rintf("%s; %d\n", buf, rez2);

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

START_TEST(test_count_equals_zero_ho)
{
    //printf("test_count_equals_zero_ho\n");
    char buf[11] = "lol";
    int n = 0;

    int rez1 = my_snprintf(buf, 0, "%ho", n);

    //printf("%s; %d\n", buf, rez1);

    char *buf1 = NULL;
    buf1 = malloc(20);
    sprintf(buf1, "%s", buf);

    snprintf(buf, 4, "%s", "lol");
    int rez2 = snprintf(buf, 0, "%ho", n);

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

Suite* my_snprintf_suite(void)
{
    Suite *s;
    TCase *tc_neg;
    TCase *tc_pos;

    // Создадим тестовый набор для тестирования функции calc_avg
    s = suite_create("my_snprintf");

    // Создадим тестовый случай из функций-тестов, которые проверяют разного
    // рода ошибочные ситуации при вызове calc_avg
    tc_neg = tcase_create("negatives");
    // Добавим в tc_neg соответствующие функции-тесты
    tcase_add_test(tc_neg, test_wrong_format);

    tcase_add_test(tc_neg, test_buf_size_equals_count_s);
    tcase_add_test(tc_neg, test_buf_size_more_than_count_s);
    tcase_add_test(tc_neg, test_count_equals_zero_but_s_is_not_empty_s);

    tcase_add_test(tc_neg, test_buf_size_equals_count_ho); //
    tcase_add_test(tc_neg, test_buf_size_more_than_count_ho); //
    tcase_add_test(tc_neg, test_count_equals_zero_but_s_is_not_empty_ho); //only rez



    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_neg);

    // Создадим тестовый случай из функций-тестов, которые проверяют работу
    // calc_avg для корректных параметров
    tc_pos = tcase_create("positives");
    // Добавим в tc_pos соответствующие функции-тесты
    tcase_add_test(tc_pos, test_buf_size_equals_count_plus_one_s);
    tcase_add_test(tc_pos, test_count_equals_zero_s);
    tcase_add_test(tc_pos, test_double_argument_s);

    tcase_add_test(tc_pos, test_buf_size_equals_count_plus_one_ho); //
    tcase_add_test(tc_pos, test_count_equals_zero_ho);
    tcase_add_test(tc_pos, test_double_argument_ho); //

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_pos);

    return s;
}

int main()
{

    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = my_snprintf_suite();
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

    return (no_failed == 0) ? EXIT_SUCCESS : EXIT_FAIL;
}
