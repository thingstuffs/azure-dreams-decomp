#include "common.h"

extern s32 D_80100AA0[];

void func_800A04B4(void) {
    s32 i;
    s32 *base = &D_80100AA0[0];
    s32 *dst;
    register s32 *src ASM_REG("$5");   /* UNRESOLVED C shape (pin): removing it changes the register colouring; the source shape that makes it unnecessary has not been found */

    i = 0;
    dst = base;
    src = base + 1;
loop:
    if (((u8 *)dst)[1] != 0) {
        *dst = *src;
        src++;
        i++;
        dst++;
        if (i < 19) {
            goto loop;
        }
    }
    base[i] = 0;
}
