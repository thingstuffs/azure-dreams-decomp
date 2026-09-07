#include "common.h"

typedef struct {
    s32 a;
    s32 b;
    s32 c;
    s32 d;
} Words;

extern s32 D_80082A38[];

void func_800AE0F4(s32 *arg0) {
    register Words *src ASM_REG("$6");
    register Words *dst ASM_REG("$7");
    register Words *end ASM_REG("$8");

    {
        register s32 *base ASM_REG("$2");

        dst = (Words *)(arg0 + 0xD);
        base = D_80082A38;
        src = (Words *)(base + 0x32);
        arg0[0xC] = base[0x20];
        end = (Words *)(base + 0x42);
        ASM_KEEP(base);
    }
    ASM_KEEP(src);
    ASM_KEEP(dst);
    ASM_KEEP(end);
    do {
        register s32 a ASM_REG("$2");
        register s32 b ASM_REG("$3");
        register s32 c ASM_REG("$4");
        register s32 d ASM_REG("$5");

        a = src->a;
        b = src->b;
        c = src->c;
        d = src->d;
        dst->a = a;
        dst->b = b;
        dst->c = c;
        dst->d = d;
        ASM_KEEP(src);
        src++;
        dst++;
    } while (src != end);
    dst->a = src->a;
}
