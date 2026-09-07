#include "common.h"

s32 func_800A6780(void) {
    register s8 *flag ASM_REG("$7") = (s8 *)0x80080000;
    register s32 *data ASM_REG("$3") = (s32 *)0x80010000;
    register s32 one ASM_REG("$6");
    s32 mode;
    s32 value;

    ASM_KEEP(flag);
    ASM_KEEP(data);
    mode = data[0x2090 / 4];
    one = 1;
    flag[0xA88] = 0;
    if (mode != one) {
        if (mode != 0) {
            return 0;
        }
        value = data[0x234 / 4];
        if (value / 5 != (value + 1) / 5) {
            return 0;
        }
    }
    flag[0xA88] = one;
    return 1;
}
