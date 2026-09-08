#include "common.h"

extern s32 D_8001029C[];

s32 func_80098FF8(void) {
    s32 count;
    s32 index;
    s32 *base;

    index = -1;
    for (count = 0; count < 20; count++) {
        if (D_8001029C[count] == 0) {
            index = count;
            break;
        }
    }
    if (index >= 0) {
        base = (s32 *)0x80010000;
        ASM_KEEP(base);   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
        base[index + 0xA8] = 0;
    }
    return (s16)index;
}
