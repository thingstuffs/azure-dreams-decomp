#include "common.h"

typedef struct {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
} Words;

extern s32 D_80082A38[];

void func_800AE0F4(s32 *arg0) {
    Words *src;
    register Words *dst ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it changes the instruction count (a copy retail keeps is dropped or added); the source shape that makes it unnecessary has not been found */
    Words *end;

    {
        s32 *base;

        dst = (Words *)(arg0 + 0xD);
        base = D_80082A38;
        src = (Words *)(base + 0x32);
        arg0[0xC] = base[0x20];
        end = (Words *)(base + 0x42);
    }
    do {
        s32 a;
        s32 b;
        s32 c;
        s32 d;

        a = src->a;
        b = src->b;
        c = src->c;
        d = src->d;
        dst->a = a;
        dst->b = b;
        dst->c = c;
        dst->d = d;
        ASM_KEEP(src);   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
        src++;
        dst++;
    } while (src != end);
    dst->a = src->a;
}
