#include "common.h"

s32 func_8004E8D8(u8 *arg0)
{
    s32 result = 0;
    s32 current;
    s32 space;
    s32 newline;
    u8 value = *arg0;

    if (value == 0) {
        goto done;
    }
    space = 0x20;
    newline = 0x0A;

loop:
    current = value & 0xFF;
    if (current == space) {
        goto next;
    }
    if (current == newline) {
        goto next;
    }
    result = 1;
    goto done;

next:
    arg0++;
    value = *arg0;
    if (value != 0) {
        goto loop;
    }

done:
    return result;
}
