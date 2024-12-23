#include "check_my_snprintf.h"

int main(void)
{
    int failed;
    
    SRunner *runner = srunner_create(my_snprintf_suite());
    srunner_run_all(runner, CK_NORMAL);
    failed = srunner_ntests_failed(runner);
    srunner_free(runner);
    return failed;
}
