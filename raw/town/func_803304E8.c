#include "common.h"

extern s32 D_80016000[3];
extern s32 D_80016000_reload[3] __asm__("D_80016000");

void func_8001ACE8(s32 arg0)
{
    register s32 value ASM_REG("$2");
    register s32 *dst ASM_REG("$6");
    s32 *src;
    s32 word_offset;
    s32 quotient;
    s32 mask;

    if (arg0 != 0) {
        value = D_80016000[0];
        ASM_KEEP(value);

        quotient = arg0;
        if (arg0 < 0) {
            quotient = arg0 + 31;
        }
        word_offset = (quotient >> 5) * 4;
        value = *(s32 *)(value + 0x18);
        dst = (s32 *)(word_offset + value);
        ASM_KEEP(dst);

        value = D_80016000_reload[0];
        ASM_KEEP(value);
        src = (s32 *)(word_offset + *(s32 *)(value + 0x18));
        ASM_KEEP(src);

        value = arg0;
        if (arg0 < 0) {
            value = arg0 + 31;
        }
        mask = 1 << (arg0 - ((value >> 5) << 5));
        ASM_KEEP(mask);
        *dst = mask | *src;
    }
}
