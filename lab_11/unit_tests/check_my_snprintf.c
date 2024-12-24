#include <check.h>
#include "check_my_snprintf.h"
#include "my_snprintf.h"

START_TEST(test_decimal)
{
    int a = 234234;
    char s_1[10], s_2[10];
    int n_1, n_2;

    n_1 = snprintf(s_1, 10, "%d", a);
    n_2 = my_snprintf(s_2, 10, "%d", a);

    ck_assert_str_eq(s_1, s_2);
    ck_assert_int_eq(n_1, n_2);
}
END_TEST

START_TEST(test_long_decimal)
{
    long int a = 13123423423;
    char s_1[10], s_2[10];
    int n_1, n_2;

    n_1 = snprintf(s_1, 10, "%ld", a);
    n_2 = my_snprintf(s_2, 10, "%ld", a);

    ck_assert_str_eq(s_1, s_2);
    ck_assert_int_eq(n_1, n_2);
}
END_TEST

START_TEST(test_short_decimal)
{
    short int a = 2130;
    char s_1[10], s_2[10];
    int n_1, n_2;

    n_1 = snprintf(s_1, 10, "%hd", a);
    n_2 = my_snprintf(s_2, 10, "%hd", a);

    ck_assert_str_eq(s_1, s_2);
    ck_assert_int_eq(n_1, n_2);
}
END_TEST

START_TEST(test_hex)
{
    unsigned int a = 0x7B;
    char s_1[10], s_2[10];
    int n_1, n_2;

    n_1 = snprintf(s_1, 10, "%x", a);
    n_2 = my_snprintf(s_2, 10, "%x", a);

    ck_assert_str_eq(s_1, s_2);
    ck_assert_int_eq(n_1, n_2);
}
END_TEST

START_TEST(test_short_hex)
{
    unsigned short int a = 0x1F4;
    char s_1[10], s_2[10];
    int n_1, n_2;

    n_1 = snprintf(s_1, 10, "%hx", a);
    n_2 = my_snprintf(s_2, 10, "%hx", a);

    ck_assert_str_eq(s_1, s_2);
    ck_assert_int_eq(n_1, n_2);
}
END_TEST

START_TEST(test_long_hex)
{
    unsigned long int a = 0x392FA;
    char s_1[10], s_2[10];
    int n_1, n_2;

    n_1 = snprintf(s_1, 10, "%lx", a);
    n_2 = my_snprintf(s_2, 10, "%lx", a);

    ck_assert_str_eq(s_1, s_2);
    ck_assert_int_eq(n_1, n_2);
}
END_TEST

START_TEST(test_oct)
{
    unsigned int a = 05634;
    char s_1[10], s_2[10];
    int n_1, n_2;

    n_1 = snprintf(s_1, 10, "%o", a);
    n_2 = my_snprintf(s_2, 10, "%o", a);

    ck_assert_str_eq(s_1, s_2);
    ck_assert_int_eq(n_1, n_2);
}
END_TEST

START_TEST(test_long_oct)
{
    unsigned long int a = 02341231;
    char s_1[10], s_2[10];
    int n_1, n_2;

    n_1 = snprintf(s_1, 10, "%lo", a);
    n_2 = my_snprintf(s_2, 10, "%lo", a);

    ck_assert_str_eq(s_1, s_2);
    ck_assert_int_eq(n_1, n_2);
}
END_TEST

START_TEST(test_short_oct)
{
    unsigned short int a = 01253;
    char s_1[10], s_2[10];
    int n_1, n_2;

    n_1 = snprintf(s_1, 10, "%ho", a);
    n_2 = my_snprintf(s_2, 10, "%ho", a);

    ck_assert_str_eq(s_1, s_2);
    ck_assert_int_eq(n_1, n_2);
}
END_TEST

START_TEST(test_percent)
{
    char s_1[10], s_2[10];
    int n_1, n_2;

    n_1 = snprintf(s_1, 10, "%%");
    n_2 = my_snprintf(s_2, 10, "%%");

    ck_assert_str_eq(s_1, s_2);
    ck_assert_int_eq(n_1, n_2);
}
END_TEST

START_TEST(test_few_args)
{
    int a = 10;
    char c = 'c';
    char *s = "string";

    char s_1[100], s_2[100];
    int n_1, n_2;

    n_1 = snprintf(s_1, 100, "Char: %c, string: %s, int: %d", c, s, a);
    n_2 = my_snprintf(s_2, 100, "Char: %c, string: %s, int: %d", c, s, a);

    ck_assert_str_eq(s_1, s_2);
    ck_assert_int_eq(n_1, n_2);
}
END_TEST

START_TEST(test_cut)
{
    int a = 50000;
    char s_1[10], s_2[10];
    int n_1, n_2;

    n_1 = snprintf(s_1, 2, "%d", a);
    n_2 = my_snprintf(s_2, 2, "%d", a);

    ck_assert_str_eq(s_1, s_2);
    ck_assert_int_eq(n_1, n_2);
}
END_TEST

START_TEST(test_i_decimal)
{
    int a = 348756;
    char s_1[10], s_2[10];
    int n_1, n_2;

    n_1 = snprintf(s_1, 2, "%i", a);
    n_2 = my_snprintf(s_2, 2, "%i", a);

    ck_assert_str_eq(s_1, s_2);
    ck_assert_int_eq(n_1, n_2);
}
END_TEST

START_TEST(test_long_i_decimal)
{
    long int a = 348723423456;
    char s_1[10], s_2[10];
    int n_1, n_2;

    n_1 = snprintf(s_1, 2, "%li", a);
    n_2 = my_snprintf(s_2, 2, "%li", a);

    ck_assert_str_eq(s_1, s_2);
    ck_assert_int_eq(n_1, n_2);
}
END_TEST

START_TEST(test_short_i_decimal)
{
    short int a = 348;
    char s_1[10], s_2[10];
    int n_1, n_2;

    n_1 = snprintf(s_1, 2, "%hi", a);
    n_2 = my_snprintf(s_2, 2, "%hi", a);

    ck_assert_str_eq(s_1, s_2);
    ck_assert_int_eq(n_1, n_2);
}
END_TEST

START_TEST(test_negative_decimal)
{
    int a = -234234;
    char s_1[10], s_2[10];
    int n_1, n_2;

    n_1 = snprintf(s_1, 10, "%d", a);
    n_2 = my_snprintf(s_2, 10, "%d", a);

    ck_assert_str_eq(s_1, s_2);
    ck_assert_int_eq(n_1, n_2);
}
END_TEST

START_TEST(test_negative_long_decimal)
{
    long int a = -13123423;
    char s_1[10], s_2[10];
    int n_1, n_2;

    n_1 = snprintf(s_1, 10, "%ld", a);
    n_2 = my_snprintf(s_2, 10, "%ld", a);

    ck_assert_str_eq(s_1, s_2);
    ck_assert_int_eq(n_1, n_2);
}
END_TEST

START_TEST(test_negative_short_decimal)
{
    short int a = -2130;
    char s_1[10], s_2[10];
    int n_1, n_2;

    n_1 = snprintf(s_1, 10, "%hd", a);
    n_2 = my_snprintf(s_2, 10, "%hd", a);

    ck_assert_str_eq(s_1, s_2);
    ck_assert_int_eq(n_1, n_2);
}
END_TEST

START_TEST(test_negative_percent)
{
    char s_1[10], s_2[10];
    int n_1, n_2;

    n_1 = snprintf(s_1, 10, "%%");
    n_2 = my_snprintf(s_2, 10, "%%");

    ck_assert_str_eq(s_1, s_2);
    ck_assert_int_eq(n_1, n_2);
}
END_TEST

START_TEST(test_negative_few_args)
{
    int a = -10;
    char c = 'c';
    char *s = "string";

    char s_1[100], s_2[100];
    int n_1, n_2;

    n_1 = snprintf(s_1, 100, "Char: %c, string: %s, int: %d", c, s, a);
    n_2 = my_snprintf(s_2, 100, "Char: %c, string: %s, int: %d", c, s, a);

    ck_assert_str_eq(s_1, s_2);
    ck_assert_int_eq(n_1, n_2);
}
END_TEST

START_TEST(test_negative_cut)
{
    int a = -50000;
    char s_1[10], s_2[10];
    int n_1, n_2;

    n_1 = snprintf(s_1, 2, "%d", a);
    n_2 = my_snprintf(s_2, 2, "%d", a);

    ck_assert_str_eq(s_1, s_2);
    ck_assert_int_eq(n_1, n_2);
}
END_TEST

START_TEST(test_negative_i_decimal)
{
    int a = -348756;
    char s_1[10], s_2[10];
    int n_1, n_2;

    n_1 = snprintf(s_1, 2, "%i", a);
    n_2 = my_snprintf(s_2, 2, "%i", a);

    ck_assert_str_eq(s_1, s_2);
    ck_assert_int_eq(n_1, n_2);
}
END_TEST

START_TEST(test_negative_long_i_decimal)
{
    long int a = -3487234;
    char s_1[10], s_2[10];
    int n_1, n_2;

    n_1 = snprintf(s_1, 2, "%li", a);
    n_2 = my_snprintf(s_2, 2, "%li", a);

    ck_assert_str_eq(s_1, s_2);
    ck_assert_int_eq(n_1, n_2);
}
END_TEST

START_TEST(test_negative_short_i_decimal)
{
    short int a = -348;
    char s_1[10], s_2[10];
    int n_1, n_2;

    n_1 = snprintf(s_1, 2, "%hi", a);
    n_2 = my_snprintf(s_2, 2, "%hi", a);

    ck_assert_str_eq(s_1, s_2);
    ck_assert_int_eq(n_1, n_2);
}
END_TEST

Suite *my_snprintf_suite(void)
{
    Suite *suite;
    TCase *decimal;
    TCase *i_decimal;
    TCase *hex;
    TCase *oct;
    TCase *valid;

    TCase *negative_decimal;
    TCase *negative_i_decimal;
    TCase *negative_hex;
    TCase *negative_oct;

    suite = suite_create("MySnprintf");
    
    decimal = tcase_create("decimal");
    hex = tcase_create("hex");
    oct = tcase_create("oct");
    valid = tcase_create("valid");
    i_decimal = tcase_create("iDecimal");

    negative_decimal = tcase_create("negative_decimal");
    negative_i_decimal = tcase_create("negative_i_decimal");
    negative_hex = tcase_create("negative_hex");
    negative_oct = tcase_create("negative_oct");

    tcase_add_test(decimal, test_decimal);
    tcase_add_test(decimal, test_long_decimal);
    tcase_add_test(decimal, test_short_decimal);

    tcase_add_test(hex, test_hex);
    tcase_add_test(hex, test_long_hex);
    tcase_add_test(hex, test_short_hex);

    tcase_add_test(oct, test_oct);
    tcase_add_test(oct, test_long_oct);
    tcase_add_test(oct, test_short_oct);

    tcase_add_test(valid, test_percent);
    tcase_add_test(valid, test_few_args);
    tcase_add_test(valid, test_cut);

    tcase_add_test(i_decimal, test_i_decimal);
    tcase_add_test(i_decimal, test_long_i_decimal);
    tcase_add_test(i_decimal, test_short_i_decimal);

    tcase_add_test(negative_decimal, test_negative_decimal);
    tcase_add_test(negative_decimal, test_negative_long_decimal);
    tcase_add_test(negative_decimal, test_negative_short_decimal);

    tcase_add_test(negative_decimal, test_negative_percent);
    tcase_add_test(negative_decimal, test_negative_few_args);
    tcase_add_test(negative_decimal, test_negative_cut);

    tcase_add_test(negative_i_decimal, test_negative_i_decimal);
    tcase_add_test(negative_i_decimal, test_negative_long_i_decimal);
    tcase_add_test(negative_i_decimal, test_negative_short_i_decimal);

    suite_add_tcase(suite, decimal);
    suite_add_tcase(suite, hex);
    suite_add_tcase(suite, oct);
    suite_add_tcase(suite, valid);
    suite_add_tcase(suite, i_decimal);
    
    suite_add_tcase(suite, negative_decimal);
    suite_add_tcase(suite, negative_hex);
    suite_add_tcase(suite, negative_oct);
    suite_add_tcase(suite, negative_i_decimal);

    return suite;
}
