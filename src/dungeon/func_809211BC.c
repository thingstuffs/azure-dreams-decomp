#include "common.h"

s32 func_800F61BC(s32 arg0, s32 arg1) {
    s32 n;
    s8 *base;
    s32 result;

    arg0 = (arg0 << 8) | (arg1 & 0xFF);
    n = 0x13;
    arg0 &= 0xFFFF;
    base = (s8 *)0x8001004C;
loop:
    result = **(u16 **)(base + 0x29C);
    if (result == arg0) {
        result = 1;
    } else {
        n--;
        base -= 4;
        if (n < 0) {
            result = 0;
        } else {
            goto loop;
        }
    }
    return result;
}
