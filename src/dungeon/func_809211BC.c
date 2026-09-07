#include "common.h"

s32 func_800F61BC(s32 arg0, s32 arg1) {
    register s8 *base ASM_REG("$3");   /* MATCH pin: retail register colouring depends on it */
    s32 result;

    arg0 = (arg0 << 8) | (arg1 & 0xFF);
    arg1 = 0x13;
    arg0 &= 0xFFFF;
    base = (s8 *)0x8001004C;
loop:
    result = **(u16 **)(base + 0x29C);
    if (result == arg0) {
        result = 1;
    } else {
        arg1--;
        base -= 4;
        if (arg1 < 0) {
            result = 0;
        } else {
            goto loop;
        }
    }
    return result;
}
