#include "arr_lib.h"
#include "check_array_funcs.h"

// Тесты для функции key

START_TEST(test_filter_empty_array)
{
    const int *src = NULL;
    int *dst_start = NULL;
    int *dst_end = NULL;
    size_t size;

    int result = prepare(src, src, &size);
    ck_assert_int_eq(result, EMPTY_ARR_ERR);
    ck_assert_ptr_null(dst_start);
    ck_assert_ptr_null(dst_end);
}
END_TEST

START_TEST(test_filter_non_empty)
{
    const int src[] = {10, 20, 30, 40, 10};
    int *dst_start = NULL;
    int *dst_end = NULL;
    size_t size;

    int result = prepare(src, src + 5, &size);
    ck_assert_int_eq(result, OK);

    dst_start = malloc(size * sizeof(int));
    ck_assert_ptr_nonnull(dst_start);

    result = key(src, src + 5, &dst_start, &dst_end);
    ck_assert_int_eq(result, OK);
    ck_assert_ptr_nonnull(dst_start);
    ck_assert(dst_start != dst_end);

    int expected[] = {40};
    ck_assert_int_eq(dst_end - dst_start, 1);
    ck_assert_int_eq(dst_start[0], expected[0]);

    free(dst_start);
}
END_TEST

START_TEST(test_filter_all_filtered_out)
{
    const int src[] = {1, 2, 3, 4, 5};
    int *dst_start = NULL;
    int *dst_end = NULL;
    size_t size;

    int result = prepare(src, src + 5, &size);
    ck_assert_int_eq(result, EMPTY_ARR_ERR);
    ck_assert_ptr_null(dst_start);
    ck_assert_ptr_null(dst_end);
}
END_TEST

Suite *key_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Filter");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_filter_empty_array);
    tcase_add_test(tc_core, test_filter_non_empty);
    tcase_add_test(tc_core, test_filter_all_filtered_out);

    suite_add_tcase(s, tc_core);

    return s;
}

// Тесты для функции mysort

START_TEST(test_sort_integers) 
{
    int arr[] = {5, 2, 9, 1, 5, 6};
    int expected[] = {1, 2, 5, 5, 6, 9};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, size, sizeof(int), int_compare);

    for (size_t i = 0; i < size; i++) {
        ck_assert_int_eq(arr[i], expected[i]);
    }
}
END_TEST

START_TEST(test_sort_sorted_array) 
{
    int arr[] = {1, 2, 3, 4, 5};
    int expected[] = {1, 2, 3, 4, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, size, sizeof(int), int_compare);

    for (size_t i = 0; i < size; i++) {
        ck_assert_int_eq(arr[i], expected[i]);
    }
}
END_TEST

START_TEST(test_sort_equal_elements) 
{
    int arr[] = {5, 5, 5, 5, 5};
    int expected[] = {5, 5, 5, 5, 5};
    size_t size = sizeof(arr) / sizeof(arr[0]);

    mysort(arr, size, sizeof(int), int_compare);

    for (size_t i = 0; i < size; i++) {
        ck_assert_int_eq(arr[i], expected[i]);
    }
}
END_TEST

START_TEST(test_sort_empty_array) 
{
    int *arr = NULL;
    size_t size = 0;

    mysort(arr, size, sizeof(int), int_compare);

    ck_assert(size == 0);
}
END_TEST

Suite *mysort_suite(void) 
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Mysort");

    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_sort_integers);
    tcase_add_test(tc_core, test_sort_sorted_array);
    tcase_add_test(tc_core, test_sort_equal_elements);
    tcase_add_test(tc_core, test_sort_empty_array);
    suite_add_tcase(s, tc_core);

    return s;
}

// Тесты для функции swap
START_TEST(test_swap_int)
{
    int a = 5, b = 10;
    swap(&a, &b, sizeof(int));
    ck_assert_int_eq(a, 10);
    ck_assert_int_eq(b, 5);
}
END_TEST

START_TEST(test_swap_double)
{
    double a = 1.23, b = 4.56;
    swap(&a, &b, sizeof(double));
    ck_assert((a - 4.56) < EPS);
    ck_assert((b - 1.23) < EPS);
}
END_TEST

START_TEST(test_swap_char_array)
{
    char a[] = "hello";
    char b[] = "world";
    swap(a, b, sizeof(a));
    ck_assert_str_eq(a, "world");
    ck_assert_str_eq(b, "hello");
}
END_TEST

Suite *swap_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("Swap");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_swap_int);
    tcase_add_test(tc_core, test_swap_double);
    tcase_add_test(tc_core, test_swap_char_array);
    suite_add_tcase(s, tc_core);

    return s;
}

// Тесты для функции int_compare
START_TEST(test_int_compare_equal)
{
    int a = 5, b = 5;
    ck_assert_int_eq(int_compare(&a, &b), 0);
}
END_TEST

START_TEST(test_int_compare_a_greater)
{
    int a = 10, b = 5;
    ck_assert(int_compare(&a, &b) > 0);
}
END_TEST

START_TEST(test_int_compare_b_greater)
{
    int a = 3, b = 8;
    ck_assert(int_compare(&a, &b) < 0);
}
END_TEST

Suite *int_compare_suite(void)
{
    Suite *s;
    TCase *tc_core;

    s = suite_create("IntCompare");
    tc_core = tcase_create("Core");

    tcase_add_test(tc_core, test_int_compare_equal);
    tcase_add_test(tc_core, test_int_compare_a_greater);
    tcase_add_test(tc_core, test_int_compare_b_greater);
    suite_add_tcase(s, tc_core);

    return s;
}
