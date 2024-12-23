#include <stdarg.h>
#include "my_snprintf.h"

static void long_int_convert(char *s, long int value)
{
    long int temp = value;
    int len = 0;
    int is_negative = 0;

    if (value == 0)
    {
        s[len++] = '0';
        s[len] = '\0';
        return;
    }

    if (value < 0)
    {
        is_negative = 1;
        value = -value;
        temp = value;
    }

    while (value != 0)
    {
        value /= 10;
        len++;
    }

    if (is_negative)
        len++;

    s[len] = '\0';
    if (is_negative)
        s[0] = '-';

    while (temp != 0)
    {
        s[--len] = (temp % 10) + '0';
        temp /= 10;
    }
}

static void short_int_convert(char *s, short int value)
{
    short int temp = value;
    int len = 0;
    int is_negative = 0;

    if (value == 0)
    {
        s[len++] = '0';
        s[len] = '\0';
        return;
    }

    if (value < 0)
    {
        is_negative = 1;
        value = -value;
        temp = value;
    }

    while (value != 0)
    {
        value /= 10;
        len++;
    }

    if (is_negative)
        len++;

    s[len] = '\0';
    if (is_negative)
        s[0] = '-';

    while (temp != 0)
    {
        s[--len] = (temp % 10) + '0';
        temp /= 10;
    }
}

static void int_convert(char *s, int value)
{
    int temp = value;
    int len = 0;
    int is_negative = 0;

    if (value == 0)
    {
        s[len++] = '0';
        s[len] = '\0';
        return;
    }

    if (value < 0)
    {
        is_negative = 1;
        value = -value;
        temp = value;
    }

    while (value != 0)
    {
        value /= 10;
        len++;
    }

    if (is_negative)
        len++;

    s[len] = '\0';
    if (is_negative)
        s[0] = '-';

    while (temp != 0)
    {
        s[--len] = (temp % 10) + '0';
        temp /= 10;
    }
}

static void oct_convert(char *s, unsigned int value)
{
    int index = 0;
    int start = 0;
    int end;
    char temp;

    if (value == 0)
        s[index++] = '0';

    while (value > 0)
    {
        s[index++] = (value % 8) + '0';
        value /= 8;
    }

    s[index] = '\0';
    end = index - 1;

    while (start < end)
    {
        temp = s[start];
        s[start] = s[end];
        s[end] = temp;
        start++;
        end--;
    }
}

static void long_oct_convert(char *s, unsigned long int value)
{
    int index = 0;
    int start = 0;
    int end;
    char temp;

    if (value == 0)
        s[index++] = '0';

    while (value > 0)
    {
        s[index++] = (value % 8) + '0';
        value /= 8;
    }

    s[index] = '\0';
    end = index - 1;

    while (start < end)
    {
        temp = s[start];
        s[start] = s[end];
        s[end] = temp;
        start++;
        end--;
    }
}

static void short_oct_convert(char *s, unsigned short int value)
{
    int index = 0;
    int start = 0;
    int end;
    char temp;

    if (value == 0)
        s[index++] = '0';

    while (value > 0)
    {
        s[index++] = (value % 8) + '0';
        value /= 8;
    }

    s[index] = '\0';
    end = index - 1;

    while (start < end)
    {
        temp = s[start];
        s[start] = s[end];
        s[end] = temp;
        start++;
        end--;
    }
}

static void hex_convert(char *s, unsigned int value)
{
    const char hex_digits[] = "0123456789abcdef";
    int index = 0;
    int start = 0;
    int end;
    char temp;

    if (value == 0)
        s[index++] = '0';

    while (value > 0)
    {
        s[index++] = hex_digits[value % 16];
        value /= 16;
    }

    s[index] = '\0';
    end = index - 1;

    while (start < end)
    {
        temp = s[start];
        s[start] = s[end];
        s[end] = temp;
        start++;
        end--;
    }
}

static void long_hex_convert(char *s, unsigned long int value)
{
    const char hex_digits[] = "0123456789abcdef";
    int index = 0;
    int start = 0;
    int end;
    char temp;

    if (value == 0)
        s[index++] = '0';

    while (value > 0)
    {
        s[index++] = hex_digits[value % 16];
        value /= 16;
    }

    s[index] = '\0';
    end = index - 1;

    while (start < end)
    {
        temp = s[start];
        s[start] = s[end];
        s[end] = temp;
        start++;
        end--;
    }
}

static void short_hex_convert(char *s, unsigned short int value)
{
    const char hex_digits[] = "0123456789abcdef";
    int index = 0;
    int start = 0;
    int end;
    char temp;

    if (value == 0)
        s[index++] = '0';

    while (value > 0)
    {
        s[index++] = hex_digits[value % 16];
        value /= 16;
    }

    s[index] = '\0';
    end = index - 1;

    while (start < end)
    {
        temp = s[start];
        s[start] = s[end];
        s[end] = temp;
        start++;
        end--;
    }
}

static void extend_string(char *dst, char *src, size_t *ind, size_t size)
{
    while(*src)
    {
        if (*ind < size - 1)
            dst[*ind] = *src;
        src++;
        (*ind)++;
    }
}

int my_snprintf(char *s, size_t size, const char *format, ...)
{
    va_list vl;
    size_t ind = 0;
    const char *p = format;
    char specifier;
    int is_long = 0, is_short = 0;
    char buff[MAX_INT_LEN];
    char *temp;

    va_start(vl, format);

    while (*p)
    {
        if (*p == '%')
        {
            if (*(p + 1) == '\0' || !(p + 1))
                return INVALID_SPECIFIER;
            p++;
            specifier = *p;

            if (specifier == 'l')
            {
                is_long = 1;
                if (*(p + 1) == '\0' || !(p + 1))
                    return INVALID_SPECIFIER;
                p++;
                specifier = *p;
            }
            else if (specifier == 'h')
            {
                is_short = 1;
                if (*(p + 1) == '\0' || !(p + 1))
                    return INVALID_SPECIFIER;
                p++;
                specifier = *p;
            }

            switch (specifier)
            {
            case 'c':
                if (is_long || is_short)
                    return INVALID_SPECIFIER;
                if (ind < size - 1)
                    s[ind] = (char)va_arg(vl, int);
                ind++;
                break;
                
            case 'd':
                if (is_long)
                    long_int_convert(buff, va_arg(vl, long));
                else if (is_short)
                    short_int_convert(buff, (short)va_arg(vl, int));
                else
                    int_convert(buff, va_arg(vl, int));
                extend_string(s, buff, &ind, size);
                break;

            case 'i':
                if (is_long)
                    long_int_convert(buff, va_arg(vl, long));
                else if (is_short)
                    short_int_convert(buff, (short)va_arg(vl, int));
                else
                    int_convert(buff, va_arg(vl, int));
                extend_string(s, buff, &ind, size);
                break;

            case 'x':
                if (is_long)
                    long_hex_convert(buff, va_arg(vl, long));
                else if (is_short)
                    short_hex_convert(buff, (short)va_arg(vl, int));
                else
                    hex_convert(buff, va_arg(vl, int));
                extend_string(s, buff, &ind, size);
                break;

            case 'o':
                if (is_long)
                    long_oct_convert(buff, va_arg(vl, long));
                else if (is_short)
                    short_oct_convert(buff, (short)va_arg(vl, int));
                else
                    oct_convert(buff, va_arg(vl, int));
                extend_string(s, buff, &ind, size);
                break;

            case 's':
                if (is_long || is_short)
                    return INVALID_SPECIFIER;
                temp = va_arg(vl, char *);
                extend_string(s, temp, &ind, size);
                break;
            case '%':
                if (ind < size - 1)
                    s[ind] = *p;
                ind++;
                break;
            default:
                return INVALID_SPECIFIER;
                break;
            }
            p++;
        }
        else
        {
            if (ind < size - 1)
                s[ind] = *p;
            ind++;
            p++;
        }

        is_long = 0;
        is_short = 0;
    }

    if (size > 0)
    {
        if (ind < size - 1)
            s[ind] = '\0';
        else
            s[size - 1] = '\0';
    }

    va_end(vl);

    return (int)ind;
}
