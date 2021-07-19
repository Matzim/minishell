#include "ft_split_whitespace_tests.h"

START_TEST(test_split_whitespace_hello_world)
{
    char *test_string = " Hello World! ";
    char **array = ft_split_whitespace(test_string);

    ck_assert_str_eq(array[0], "Hello");
    ck_assert_str_eq(array[1], "World!");
    ck_assert_ptr_eq(array[2], NULL);
}
END_TEST

START_TEST(test_split_whitespace_full_blank)
{
    char *test_string = "      \t  \n \r   ";
    char **array = ft_split_whitespace(test_string);

    ck_assert_ptr_eq(array[0], NULL);
}
END_TEST

START_TEST(test_split_whitespace)
{
    char *test_string = "Split the string into each spaces!";
    char **array = ft_split_whitespace(test_string);

    ck_assert_str_eq(array[0], "Split");
    ck_assert_str_eq(array[1], "the");
    ck_assert_str_eq(array[2], "string");
    ck_assert_str_eq(array[3], "into");
    ck_assert_str_eq(array[4], "each");
    ck_assert_str_eq(array[5], "spaces!");
    ck_assert_ptr_eq(array[6], NULL);
}
END_TEST

START_TEST(test_split_whitespace_more)
{
    char *test_string = "More \n\r blank characters\t";
    char **array = ft_split_whitespace(test_string);

    ck_assert_str_eq(array[0], "More");
    ck_assert_str_eq(array[1], "blank");
    ck_assert_str_eq(array[2], "characters");
    ck_assert_ptr_eq(array[3], NULL);
}
END_TEST

Suite *ft_split_whitespace_testsuite(void)
{
    Suite *s = suite_create("ft_split_whitespace testsuite");

    /* Creation test case */
    TCase *tc_core = tcase_create("ft_split_whitespace");

    tcase_add_test(tc_core, test_split_whitespace_hello_world);
    tcase_add_test(tc_core, test_split_whitespace);
    tcase_add_test(tc_core, test_split_whitespace_more);
    tcase_add_test(tc_core, test_split_whitespace_full_blank);
    suite_add_tcase(s, tc_core);

    return s;
}
