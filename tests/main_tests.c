#include <stdlib.h>

#include "libft_tests/ft_atoi_tests.h"
#include "libft_tests/ft_split_whitespace_tests.h"
#include "libft_tests/ft_strjoin_tests.h"
#include "libft_tests/ft_strlen_tests.h"

int main(void)
{
    SRunner *sr = srunner_create(ft_atoi_testsuite());

    srunner_add_suite(sr, ft_strlen_testsuite());
    srunner_add_suite(sr, ft_strjoin_testsuite());
    srunner_add_suite(sr, ft_split_whitespace_testsuite());

    srunner_set_fork_status(sr, CK_NOFORK);
    srunner_set_log(sr, "test.log");
    srunner_set_xml(sr, "test.xml");
    srunner_run_all(sr, CK_VERBOSE);

    int number_failed = srunner_ntests_failed(sr);
    srunner_free(sr);
    return (number_failed == 0) ? EXIT_SUCCESS : EXIT_FAILURE;
}
