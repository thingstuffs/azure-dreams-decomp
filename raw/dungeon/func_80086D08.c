#include "common.h"

#define FIELD(p, t, off) (*(t *)((u8 *)(p) + (off)))

extern s16 D_80083228;
extern u8 D_800DD050[];
extern u8 D_800DD0E0[];

extern void func_80048A44(void *, s16, s16, s32);
extern void func_8008C4C8(void *, u8 *);

void func_8008C468(void *arg0, void *arg1, void *arg2, void *arg3) {
    if (!(FIELD(arg0, u16, 0x98) & 0xC)) {
        FIELD(arg0, u8, 0x9A) = 0x16;
        FIELD(arg0, u8, 0x9B) = 0;
        FIELD(arg0, s32, 0x8C) = 0;
        FIELD(arg0, u16, 0xA2) &= 0xFFFE;
        if (FIELD(arg3, s32, 0x1C) & 0x100000) {
#ifndef NON_MATCHING
            register u8 *page_v0 ASM_REG("$2");
#endif
            register u8 *dead_v1 ASM_REG("$3");

#ifndef NON_MATCHING
            page_v0 = (u8 *)0x800E0000;
            ASM_KEEP(page_v0);
#endif
            dead_v1 = FIELD(arg2, u8 * volatile, 0x2C);
            ASM_KEEP(dead_v1);
#ifndef NON_MATCHING
            return func_8008C4C8(arg0, page_v0 - 0x2F20);
#else
            return func_8008C4C8(arg0, D_800DD0E0);
#endif
        }
        if (FIELD(arg2, u8 *, 0x2C) != D_800DD050) {
            register void *call_arg ASM_REG("$4");

            call_arg = arg2;
            FIELD(call_arg, u8 *, 0x2C) = D_800DD050;
            func_80048A44(call_arg, D_800DD050[((D_80083228 + FIELD(arg3, s16, 0x2A) + 0x100) >> 9) & 7], 0, 1);
        }
    }
}
