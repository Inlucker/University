#include "functions.h"
#include <check.h>

/*int mysort_test()
{
    int rez = 0;

    int n = 0;
    void *mas = NULL;

    n = 10;
    int *mas_int = NULL;
    mas_int = calloc(n, sizeof (int));
    for (int i = 0; i < n; i++)
    {
        mas_int[i] = n - i;
    }

    mas = mas_int;

    mysort(mas, n, sizeof (int), (int(*)(const void *, const void *)) comp_int);

    int areEqual = 1;
    for (int i = 0; i < n; i++)
    {
        if (mas_int[i] != i + 1)
            areEqual = 0;
    }

    if (!areEqual)
        rez++;

    return rez;
}*/

START_TEST(test_mysort)
{
    int n = 10;
    int *mas = NULL;
    mas = calloc(n, sizeof (int));
    for (int i = 0; i < n; i++)
    {
        mas[i] = n - i;
    }

    //mas = mas_int;

    mysort(mas, n, sizeof (int), (int(*)(const void *, const void *)) comp_int);

    int areEqual = 1;
    for (int i = 0; i < n; i++)
    {
        if (mas[i] != i + 1)
            areEqual = 0;
    }

    free(mas);

    ck_assert_int_eq(areEqual, 1);
}
END_TEST

START_TEST(test_key_input_zero_elems_after_key)
{
    int n = 10;
    int *mas = NULL;
    mas = calloc(n, sizeof (int));

    for (int i = 0; i < n; i++)
    {
        mas[i] = 1;
    }

    int *mas_end = &mas[n];
    int *mas_f = NULL;
    int *mas_f_end = NULL;

    int rez = key(mas, mas_end, &mas_f, &mas_f_end);

    free(mas);

    ck_assert_int_eq(rez, FILTR_ERROR);
}
END_TEST

START_TEST(test_key_input_same_ptrs)
{
    int n = 2;
    int *mas = NULL;
    mas = calloc(n, sizeof (int));

    for (int i = 0; i < n; i++)
    {
        mas[i] = n - i;
    }

    int *mas_end = &mas[0];
    int *mas_f = NULL;
    int *mas_f_end = NULL;

    int rez = key(mas, mas_end, &mas_f, &mas_f_end);

    free(mas);

    ck_assert_int_eq(rez, FILTR_ERROR);
}
END_TEST

START_TEST(test_key_input_wrong_data)
{
    int n = 10;
    int *mas = NULL;
    mas = calloc(n, sizeof (int));

    for (int i = 0; i < n; i++)
    {
        mas[i] = n - i;
    }

    int *mas_end = &mas[n];
    int *mas_f = NULL;
    int *mas_f_end = NULL;

    int rez = key(mas_end, mas, &mas_f, &mas_f_end);

    free(mas);

    ck_assert_int_eq(rez, FILTR_ERROR);
}
END_TEST

START_TEST(test_key)
{
    int n = 10;
    int *mas = NULL;
    mas = calloc(n, sizeof (int));

    for (int i = 0; i < n; i++)
    {
        mas[i] = n - i;
    }

    int *mas_end = &mas[n];
    int *mas_f = NULL;
    int *mas_f_end = NULL;

    int rez = key(mas, mas_end, &mas_f, &mas_f_end);

    int m = (mas_f_end - mas_f);
    output("output3.txt", mas_f, m);

    int areEqual = 1;
    for (int i = 0; i < m; i++)
    {
        if (mas[i] != n - i)
            areEqual = 0;
    }

    free(mas);
    free(mas_f);

    ck_assert_int_eq(rez, 0);
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
    tcase_add_test(tc_neg, test_key_input_same_ptrs);
    tcase_add_test(tc_neg, test_key_input_zero_elems_after_key);
    tcase_add_test(tc_neg, test_key_input_wrong_data);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_neg);

    // Создадим тестовый случай из функций-тестов, которые проверяют работу
    // calc_avg для корректных параметров
    tc_pos = tcase_create("positives");
    // Добавим в tc_pos соответствующие функции-тесты
    tcase_add_test(tc_pos, test_mysort);
    tcase_add_test(tc_pos, test_key);


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
