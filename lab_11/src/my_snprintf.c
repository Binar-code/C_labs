#include <stdarg.h>
#include "my_snprintf.h"

static void decimal_convert(char *s, long int value, int base) 
{
    int is_negative = (value < 0 && base == 10);
    char temp[32];
    size_t index = 0;
    size_t ind = 0;
    unsigned long abs_value;
    int digit;

    if (value < 0)
        abs_value = -(unsigned long)value;
    else 
        abs_value = (unsigned long)value;

    if (abs_value == 0)
        temp[index++] = '0';

    while (abs_value > 0) 
    {
        digit = abs_value % base;
        temp[index++] = (digit < 10) ? (digit + '0') : (digit - 10 + 'a');
        abs_value /= base;
    }

    if (is_negative)
        temp[index++] = '-';

    for (size_t i = index; i > 0; i--)
        s[ind++] = temp[i - 1];

    s[ind] = '\0';
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
                    decimal_convert(buff, va_arg(vl, long), 10);
                else if (is_short)
                    decimal_convert(buff, (short)va_arg(vl, int), 10);
                else
                    decimal_convert(buff, va_arg(vl, int), 10);
                extend_string(s, buff, &ind, size);
                break;

            case 'i':
                if (is_long)
                    decimal_convert(buff, va_arg(vl, long), 10);
                else if (is_short)
                    decimal_convert(buff, (short)va_arg(vl, int), 10);
                else
                    decimal_convert(buff, va_arg(vl, int), 10);
                extend_string(s, buff, &ind, size);
                break;

            case 'x':
                if (is_long)
                    decimal_convert(buff, va_arg(vl, long), 16);
                else if (is_short)
                    decimal_convert(buff, (short)va_arg(vl, int), 16);
                else
                    decimal_convert(buff, va_arg(vl, int), 16);
                extend_string(s, buff, &ind, size);
                break;

            case 'o':
                if (is_long)
                    decimal_convert(buff, va_arg(vl, long), 8);
                else if (is_short)
                    decimal_convert(buff, (short)va_arg(vl, int), 8);
                else
                    decimal_convert(buff, va_arg(vl, int), 8);
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
