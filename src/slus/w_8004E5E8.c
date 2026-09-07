#include "common.h"

extern void func_8004E4C0(int value, unsigned short width, char *buf, int pad);
extern char *reverseBytes(char *buf, unsigned short width);

/* Format `value` into `buf` right-justified in `width` columns, zero-padded, then return `buf`. */
char *formatIntZeroPadded(int value, unsigned short width, char *buf, int unused)
{
    func_8004E4C0(value, width, buf, '0');
    reverseBytes(buf, width);
    return buf;
}
