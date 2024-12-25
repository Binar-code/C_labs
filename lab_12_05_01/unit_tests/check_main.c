#include <check.h>
#include "check_array_funcs.h"

int main(void)
{
    int failed;

    SRunner *runner = srunner_create(key_suite());
    srunner_add_suite(runner, mysort_suite());
    srunner_add_suite(runner, swap_suite());
    srunner_add_suite(runner, int_compare_suite());

    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);

    return failed;
}
