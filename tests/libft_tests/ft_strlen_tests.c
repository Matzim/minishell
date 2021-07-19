#include "ft_strlen_tests.h"

START_TEST(test_strlen_positive_number)
{
    ck_assert_int_eq(ft_strlen("5"), 1);
    ck_assert_int_eq(ft_strlen("Library"), 7);
    ck_assert_int_eq(ft_strlen("     World  "), 12);
}
END_TEST

START_TEST(test_strlen_special)
{
    ck_assert_int_eq(ft_strlen(""), 0);
    ck_assert_int_eq(ft_strlen("AZ\0x3648"), 2);
}
END_TEST

Suite *ft_strlen_testsuite(void)
{
    Suite *s = suite_create("ft_strlen testsuite");

    /* Creation test case */
    TCase *tc_core = tcase_create("ft_strlen");

    tcase_add_test(tc_core, test_strlen_positive_number);
    tcase_add_test(tc_core, test_strlen_special);
    suite_add_tcase(s, tc_core);

    return s;
}
