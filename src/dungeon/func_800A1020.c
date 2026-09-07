#include "common.h"

s32 func_800A6780(void) {
    register s8 *flag ASM_REG("$7") = (s8 *)0x80080000;   /* MATCH pin: retail register colouring depends on it */
    register s32 *data ASM_REG("$3") = (s32 *)0x80010000;   /* MATCH pin: retail branch polarity depends on it */
    s32 one;
    s32 mode;
    s32 value;

    ASM_KEEP(flag);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ASM_KEEP(data);   /* MATCH pin: keeps a constant in a register as retail does */
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
