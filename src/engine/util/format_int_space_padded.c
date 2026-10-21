#include "common.h"
#include "engine/util.h"

/* Format a space-padded integer, reverse its width characters in place, and return buf. */
char *format_int_space_padded(int value, unsigned short width, char *buf)
{
    format_reversed_decimal_space_padded(value, width, buf);
    reverse_bytes(buf, width);
    return buf;
}
