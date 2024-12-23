#ifndef _MY_SNPRINTF__
#define _MY_SNPRINTF__

#include <stdio.h>

#define INVALID_SPECIFIER -1

#define MAX_INT_LEN 21

int my_snprintf(char *s, size_t size, const char *format, ...);

#endif
