#include "common.h"

extern void formatReversedUnsignedDecimal(int value, unsigned short width, char *buf, int pad);
extern char *reverseBytes(char *buf, unsigned short width);

/* Format value right-justified with zero padding to width columns and return buf. */
char *formatIntZeroPadded(int value, unsigned short width, char *buf, int unused)
{
    formatReversedUnsignedDecimal(value, width, buf, '0');
    reverseBytes(buf, width);
    return buf;
}
