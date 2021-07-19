#include "ft_strjoin_tests.h"

START_TEST(test_strjoin)
{
    ck_assert_str_eq(ft_strjoin("Hello", " World!"), "Hello World!");
    ck_assert_str_eq(
        ft_strjoin("ABCDEFGHIJKLMNOPQRSTUVWXYZ", "abcdefghijklmnopqrstuvwxyz"),
        "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz");
    ck_assert_str_eq(ft_strjoin("", ""), "");
}
END_TEST

Suite *ft_strjoin_testsuite(void)
{
    Suite *s = suite_create("ft_strjoin testsuite");

    /* Creation test case */
    TCase *tc_core = tcase_create("ft_strjoin");

    tcase_add_test(tc_core, test_strjoin);
    suite_add_tcase(s, tc_core);

    return s;
}
