#include "common.h"

/* Format `value` into `buf` (space-padded, right-justified in `width` columns) then reverse the resulting characters in place; returns buf. */
char *formatIntSpacePadded(int value, unsigned short width, char *buf)
{
    func_8004E57C(value, width, buf);
    reverseBytes(buf, width);
    return buf;
}
