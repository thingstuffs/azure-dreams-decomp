#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern u8 D_80024B20[];
#ifndef NON_MATCHING
extern u8 D_80020000[];
__asm__(".set D_80020000, 0x80020000");
#else
#define D_80020000 (D_80024B20 - 0x4B20)
#endif
extern void func_80025038(void) __attribute__((noreturn));
extern void func_8004491C();
extern s16 func_8006649C();
extern s32 func_80069EF8(void);

void func_819A764C(void *arg0)
{
    s16 delta[3];
    s32 state;
    register s32 i ASM_REG("$16");
    register void *dst ASM_REG("$17");
    void *tail_arg;
    void *inner;
    register u32 page_base ASM_REG("$3");
    register u8 *message ASM_REG("$5");
    register void *self ASM_REG("$18") = arg0;

    ASM_KEEP(self);
    inner = FIELD(self, void *, 0);
    FIELD(inner, u16, 0x52) |= 0x8000;

    delta[0] = (FIELD(self, s16, 0x24) - FIELD(self, s16, 4)) >> 2;
    delta[1] = (FIELD(self, s16, 0x26) - FIELD(self, s16, 6)) >> 2;
    delta[2] = (FIELD(self, s16, 0x28) - FIELD(self, s16, 8)) >> 2;
    i = 1;
    dst = self + 8;
    ASM_KEEP(dst);

    do {
        FIELD(dst, s16, 4) = FIELD(self, u16, 4) + delta[0] * i
                            + (func_80069EF8() & 0x3F) - 0x20;
        FIELD(dst, s16, 6) = FIELD(self, u16, 6) + delta[1] * i
                            + (func_80069EF8() & 0x3F) - 0x20;
        FIELD(dst, s16, 8) = FIELD(self, u16, 8) + delta[2] * i++
                            - (func_80069EF8() & 0x3F);
        dst += 8;
    } while (i < 4);

    FIELD(self, s16, 0x2C) = ((FIELD(self, u16, 0x3E) & 3) << 5) + 0x80;
    state = FIELD(self, s16, 0x3C);
    FIELD(self, s16, 0x2E) = ((s16)FIELD(self, u16, 0x3E) >> 2) << 5;

    if (state == 1) {
        goto state_one;
    }
    if (state >= 2) {
        goto high_states;
    }
    tail_arg = self - 0x20;
    if (state == 0) {
        goto state_zero;
    }
    func_80025038();

high_states:
    if (state == 2) {
        goto state_two;
    }
    func_80025038();

state_zero:
    message = D_80020000;
    ASM_KEEP(message);
    message += 0x4B20;
    func_8004491C(tail_arg, message);

state_one:
    FIELD(self, u16, 0x3E) = (func_80069EF8() & 3) + 2;
    FIELD(self, s32, 0x38) += 0xFFF7F7F8;
    FIELD(self, s16, 0x42) = func_8006649C((func_80069EF8() & 0xF) << 4, 0x1F8);
    FIELD(self, u16, 0x3C)++;
    func_80025038();

state_two:
    page_base = 0x80080000;
    ASM_KEEP(page_base);
    FIELD(self, u16, -2) |= 0x8000;
    FIELD((void *)page_base, u32, 0x14A0) |= 0x8000;
}
