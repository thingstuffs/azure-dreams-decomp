#include "common.h"

s32 func_8009904C(s32 arg0) {
    register s32 *entry ASM_REG("$5");
    register s32 i ASM_REG("$3") = 0;
    s32 value;

    entry = (s32 *)0x80010000;
loop:
    value = entry[0xA7];
    if (value != 0) {
        if (value != arg0) {
            i++;
            entry++;
            if (i < 20) {
                goto loop;
            }
        } else {
            return (s16)i;
        }
    }
    return -1;
}
