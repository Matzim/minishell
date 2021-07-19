#include "ft_atoi_tests.h"

START_TEST(test_atoi_positive_number)
{
    ck_assert_int_eq(ft_atoi("5"), 5);
    ck_assert_int_eq(ft_atoi("123424"), 123424);
    ck_assert_int_eq(ft_atoi("500002"), 500002);
    ck_assert_int_eq(ft_atoi("99999"), 99999);
    ck_assert_int_eq(ft_atoi("12"), 12);
}
END_TEST

START_TEST(test_atoi_negative_number)
{
    ck_assert_int_eq(ft_atoi("-5"), -5);
    ck_assert_int_eq(ft_atoi("-123424"), -123424);
    ck_assert_int_eq(ft_atoi("-500002"), -500002);
    ck_assert_int_eq(ft_atoi("-99999"), -99999);
    ck_assert_int_eq(ft_atoi("-12"), -12);
}
END_TEST

START_TEST(test_atoi_special)
{
    ck_assert_int_eq(ft_atoi("0"), 0);
    ck_assert_int_eq(ft_atoi("2147483647"), 2147483647);
    ck_assert_int_eq(ft_atoi("-2147483648"), -2147483648);
}
END_TEST

START_TEST(test_atoi_end_before)
{
    ck_assert_int_eq(ft_atoi("5A"), 5);
}
END_TEST

Suite *ft_atoi_testsuite(void)
{
    Suite *s = suite_create("ft_atoi testsuite");

    /* Creation test case */
    TCase *tc_core = tcase_create("ft_atoi");

    tcase_add_test(tc_core, test_atoi_positive_number);
    tcase_add_test(tc_core, test_atoi_negative_number);
    tcase_add_test(tc_core, test_atoi_special);
    tcase_add_test(tc_core, test_atoi_end_before);
    suite_add_tcase(s, tc_core);

    return s;
}
