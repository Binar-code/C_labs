#include <stdlib.h>
#include "arr_lib.h"
#include "check_arr_lib.h"

START_TEST(test_empty_array)
{
    int src[4] = {0};
    int *dst = NULL;
    size_t new_size;

    int result = filter(dst, &new_size, src, 0);

    ck_assert_int_eq(result, SIZE_ERR);
}
END_TEST

START_TEST(test_unique_elements)
{
    int src[] = {1, 2, 3, 4, 5};
    size_t size = 5;
    int dst[5];
    size_t new_size;

    int result = filter(dst, &new_size, src, size);

    ck_assert_int_eq(result, OK);
    ck_assert_int_eq(new_size, 5);
    for (size_t i = 0; i < size; i++)
        ck_assert_int_eq(dst[i], src[i]);
}
END_TEST

START_TEST(test_with_duplicates)
{
    int src[] = {1, 2, 2, 3, 3, 3};
    size_t size = 6;
    int dst[6];
    size_t new_size;

    int result = filter(dst, &new_size, src, size);

    ck_assert_int_eq(result, OK);
    ck_assert_int_eq(new_size, 3);
    ck_assert_int_eq(dst[0], 1);
    ck_assert_int_eq(dst[1], 2);
    ck_assert_int_eq(dst[2], 3);
}
END_TEST

START_TEST(test_null_dst)
{
    int src[] = {1, 1, 2, 3, 3};
    size_t size = 5;
    size_t new_size;

    int result = filter(NULL, &new_size, src, size);

    ck_assert_int_eq(result, OK);
    ck_assert_int_eq(new_size, 3);
}
END_TEST

Suite *filter_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Filter");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_empty_array);
    tcase_add_test(tc_core, test_unique_elements);
    tcase_add_test(tc_core, test_with_duplicates);
    tcase_add_test(tc_core, test_null_dst);
    suite_add_tcase(s, tc_core);

    return s;
}

START_TEST(test_fib_arr_correct_fill)
{
    int arr[5];
    int expected[] = {1, 1, 2, 3, 5};

    int result = fib_arr(arr, 5);

    ck_assert_int_eq(result, OK);
    for (size_t i = 0; i < 5; i++)
        ck_assert_int_eq(arr[i], expected[i]);
}
END_TEST

START_TEST(test_fib_arr_zero_size)
{
    int arr[5];
    int result = fib_arr(arr, 0);

    ck_assert_int_eq(result, OK);
}
END_TEST

START_TEST(test_fib_arr_null_pointer)
{
    int *arr = NULL;
    int result = fib_arr(arr, 5);

    ck_assert_int_eq(result, SIZE_ERR);
}
END_TEST

START_TEST(test_fib_arr_large_size)
{
    int arr[20];
    int expected[] = {1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144, 233, 377, 610, 987, 1597, 2584, 4181, 6765};

    int result = fib_arr(arr, 20);

    ck_assert_int_eq(result, OK);
    for (size_t i = 0; i < 20; i++)
        ck_assert_int_eq(arr[i], expected[i]);
}
END_TEST

Suite *fib_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Fib");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_fib_arr_correct_fill);
    tcase_add_test(tc_core, test_fib_arr_zero_size);
    tcase_add_test(tc_core, test_fib_arr_null_pointer);
    tcase_add_test(tc_core, test_fib_arr_large_size);
    suite_add_tcase(s, tc_core);

    return s;
}
