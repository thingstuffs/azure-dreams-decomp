#include "common.h"
#include "engine/text.h"
#include "engine/util.h"

/* Format value right-justified with zero padding to width columns and return buf. */
char *format_int_zero_padded(int value, unsigned short width, char *buf, int unused)
{
    format_reversed_unsigned_decimal(value, width, buf, '0');
    reverse_bytes(buf, width);
    return buf;
}
