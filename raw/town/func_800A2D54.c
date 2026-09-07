#include "common.h"

extern s32 D_80100AA0[];

void func_800A04B4(void) {
    s32 i;
    s32 *base = &D_80100AA0[0];
    register s32 *dst ASM_REG("$3");
    register s32 *src ASM_REG("$5");

    i = 0;
    dst = base;
    src = base + 1;
    ASM_KEEP(dst);
    ASM_KEEP(src);
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
