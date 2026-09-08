#include "common.h"

/* Format a space-padded integer, reverse its width characters in place, and return buf. */
char *formatIntSpacePadded(int value, unsigned short width, char *buf)
{
    func_8004E57C(value, width, buf);
    reverseBytes(buf, width);
    return buf;
}
