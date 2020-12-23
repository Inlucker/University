#include "io_functions.h"
#include "mtrx_functions.h"
#include <check.h>

#define EPS 1e-7

/*START_TEST(test_read_args)
{
    int argc = 2;
    char **argv = NULL;
    argv = malloc(50 * 2 * (sizeof (char)));
    argv[0] = "wrong_number_of_arguments";
    argv[1] = "neg_01_out.txt";

    char file_name1[M] = "";
    char file_name2[M] = "";
    char rez_file_name[M] = "";
    int action_id = 0;

    int rez = read_args(argc, argv, &action_id, file_name1, file_name2, rez_file_name);

    ck_assert_int_eq(rez, CONSOLE_ARGS_ERROR);
}
END_TEST*/

START_TEST(test_read_file)
{
    double **mtrx1_ptrs = NULL;
    int columns1 = 0, rows1 = 0;

    //printf("%p\n", mtrx1_ptrs);
    mtrx1_ptrs = read_mtrx_from_file("doesnt_exist.txt", &rows1, &columns1); //, &mtrx1

    ck_assert_ptr_eq(mtrx1_ptrs, NULL);
    /*if (mtrx1_ptrs != NULL)
        free_mtrx(mtrx1_ptrs);*/
}
END_TEST

START_TEST(test_solvation_no_answer)
{
    double **mtrx1_ptrs = NULL;
    int columns = 4, rows = 3;

    mtrx1_ptrs = matrix_malloc2(rows, columns);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
        {
            mtrx1_ptrs[i][j] = j + 1;
        }

    //print_mtrx(mtrx1_ptrs, rows, columns);

    double **rez_mtrx_ptrs = NULL;
    rez_mtrx_ptrs = matrix_malloc2(rows, 1);

    double **rez = solve_mtrx(mtrx1_ptrs, rows, columns); //, rez_mtrx
    if (rez != NULL)
        rez_mtrx_ptrs = rez;

    //print_mtrx(rez_mtrx_ptrs, rows, 1);

    ck_assert_ptr_eq(rez, NULL);

    free_mtrx(mtrx1_ptrs);
    free_mtrx(rez_mtrx_ptrs);
}
END_TEST

START_TEST(test_mtrx_addition)
{
    double **mtrx1_ptrs = NULL;
    //double *mtrx2 = NULL;
    //double **mtrx2_ptrs = NULL;
    int columns = 3, rows = 4;

    mtrx1_ptrs = matrix_malloc2(rows, columns);
    //mtrx2_ptrs = matrix_malloc(&mtrx2, rows, columns);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
        {
            mtrx1_ptrs[i][j] = i + j;
            //mtrx2_ptrs[i][j] = i + j;
        }

    double **rez_mtrx_ptrs = NULL;
    rez_mtrx_ptrs = matrix_malloc2(rows, columns);

    mtrx_addition(mtrx1_ptrs, mtrx1_ptrs, rez_mtrx_ptrs, rows, columns);


    int areEqual = 1;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
        {
            if (rez_mtrx_ptrs[i][j] - (2*(i + j)) > EPS)
                areEqual = 0;
        }

    ck_assert_int_eq(areEqual, 1);

    free_mtrx(mtrx1_ptrs);
    free_mtrx(rez_mtrx_ptrs);
}
END_TEST

START_TEST(test_mtrx_composition)
{
    double **mtrx1_ptrs = NULL;
    int columns = 3, rows = 3;

    mtrx1_ptrs = matrix_malloc2(rows, columns);

    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
        {
            mtrx1_ptrs[i][j] = j + 1;
        }

    double **rez_mtrx_ptrs = NULL;
    rez_mtrx_ptrs = matrix_malloc2(rows, columns);

    mtrx_composition(mtrx1_ptrs, mtrx1_ptrs, rez_mtrx_ptrs, rows, columns, columns);

    int areEqual = 1;
    for (int i = 0; i < rows; i++)
        for (int j = 0; j < columns; j++)
        {
            if (rez_mtrx_ptrs[i][j] - (6*(j+1)) > EPS)
                areEqual = 0;
        }

    ck_assert_int_eq(areEqual, 1);

    free_mtrx(mtrx1_ptrs);
    free_mtrx(rez_mtrx_ptrs);
}
END_TEST

START_TEST(test_mtrx_solvation)
{
    double **mtrx_ptrs = NULL;
    int columns = 4, rows = 3;

    mtrx_ptrs = matrix_malloc2(rows, columns);

    for (int j = 0; j < columns; j++)
    {
        mtrx_ptrs[0][j] = j + 1;
    }
    for (int j = 0; j < columns; j++)
    {
        mtrx_ptrs[1][j] = 2 * columns - j;
    }
    mtrx_ptrs[2][0] = 25;
    mtrx_ptrs[2][1] = 37;
    mtrx_ptrs[2][2] = 48;
    mtrx_ptrs[2][3] = 52;

    //print_mtrx(mtrx1_ptrs, rows, columns);

    double **rez_mtrx_ptrs = solve_mtrx(mtrx_ptrs, rows, columns); //, rez_mtrx

    //print_mtrx(rez_mtrx_ptrs, rows, 1);

    int areEqual = 1;

    if (rez_mtrx_ptrs[0][0] - 7.0 > EPS)
        areEqual = 0;
    if (rez_mtrx_ptrs[1][0] + 15.0 > EPS)
        areEqual = 0;
    if (rez_mtrx_ptrs[2][0] - 9.0 > EPS)
        areEqual = 0;

    ck_assert_int_eq(areEqual, 1);

    free_mtrx(mtrx_ptrs);
    free_mtrx(rez_mtrx_ptrs);
}
END_TEST

Suite* mtrx_functions_suite(void)
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
    //tcase_add_test(tc_neg, test_read_args);
    tcase_add_test(tc_neg, test_read_file);
    tcase_add_test(tc_neg, test_solvation_no_answer);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_neg);

    // Создадим тестовый случай из функций-тестов, которые проверяют работу
    // calc_avg для корректных параметров
    tc_pos = tcase_create("positives");
    // Добавим в tc_pos соответствующие функции-тесты
    tcase_add_test(tc_pos, test_mtrx_addition);
    tcase_add_test(tc_pos, test_mtrx_composition);
    tcase_add_test(tc_pos, test_mtrx_solvation);

    // Добавим сформированный тестовый случай в тестовый набор
    suite_add_tcase(s, tc_pos);

    return s;
}

int main()
{

    int no_failed = 0;
    Suite *s;
    SRunner *runner;

    s = mtrx_functions_suite();
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
