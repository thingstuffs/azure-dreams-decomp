#include "common.h"

extern s32 D_80016000[3];
extern s32 D_80016000_reload[3] __asm__("D_80016000");

void func_8001ACE8(s32 arg0)
{
    register s32 value ASM_REG("$2");   /* UNRESOLVED C shape (pin): removing it moves a statement across a call/branch; the source shape that makes it unnecessary has not been found */
    s32 *dst;
    s32 *src;
    s32 word_offset;
    s32 quotient;
    s32 mask;

    if (arg0 != 0) {
        value = D_80016000[0];

        quotient = arg0;
        if (arg0 < 0) {
            quotient = arg0 + 31;
        }
        word_offset = (quotient >> 5) * 4;
        value = *(s32 *)(value + 0x18);
        dst = (s32 *)(word_offset + value);

        value = D_80016000_reload[0];
        src = (s32 *)(word_offset + *(s32 *)(value + 0x18));
        ASM_KEEP(src);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */

        value = arg0;
        if (arg0 < 0) {
            value = arg0 + 31;
        }
        mask = 1 << (arg0 - ((value >> 5) << 5));
        ASM_KEEP(mask);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
        *dst = mask | *src;
    }
}
