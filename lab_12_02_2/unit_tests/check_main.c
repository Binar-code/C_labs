#include <check.h>
#include <check_arr_lib.h>

int main(void)
{
    int failed;
    SRunner *sr;
    
    sr = srunner_create(filter_suite());
    srunner_add_suite(sr, fib_suite());

    srunner_run_all(sr, CK_NORMAL);
    failed = srunner_ntests_failed(sr);
    srunner_free(sr);

    return failed;
}
