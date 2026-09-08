#include "common.h"

s32 func_800A6780(void) {
    register s8 *flag ASM_REG("$7") = (s8 *)0x80080000;   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */
    register s32 *data ASM_REG("$3") = (s32 *)0x80010000;   /* UNRESOLVED C shape (pin): removing it flips a branch polarity; the source shape that makes it unnecessary has not been found */
    s32 one;
    s32 mode;
    s32 value;

    ASM_KEEP(flag);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    ASM_KEEP(data);   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
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
