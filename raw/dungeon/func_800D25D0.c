#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_800478B8(void *);
extern s32 func_800644B8(s32);
extern s32 func_80064584(s32);
extern s32 rand(void);
extern void func_800D7F1C();
extern s32 D_800814A0;
extern u16 D_80083460[];

void func_800D7D30(void *arg0, void *arg1, void *arg2) {
    register s32 x ASM_REG("$2");
    s32 z;
    s32 dz;
    s32 value;
    u32 c0;
    u32 c1;
    u32 c2;
    s16 state;

    z = FIELD(arg1, s32, 0x10);
    dz = FIELD(arg1, s32, 0x14);
    FIELD(arg1, s32, 0) += FIELD(arg1, s32, 0xC);
    FIELD(arg1, s32, 4) += z;
    FIELD(arg1, s32, 8) += dz;

    state = FIELD(arg0, s16, 0x4C);
    if (state != 0) {
        if (state == 1) {
            goto state_one;
        }
        func_800D7F1C(z, dz);
        return;
    }

    func_800478B8(arg2);
    if (FIELD(arg2, u16, 0x14) & 0x6000) {
        FIELD(arg2, s8, 4) = 0;
        FIELD(arg2, s8, 5) = 0;
    }

    FIELD(arg1, s16, 2) = (s16)(FIELD(arg0, u16, 0xC) +
        ((func_800644B8(FIELD(arg0, s16, 0x18)) *
          FIELD(arg0, s16, 0x1E)) >> 12));
    FIELD(arg1, s16, 6) = (s16)(FIELD(arg0, u16, 0xE) +
        ((func_80064584(FIELD(arg0, s16, 0x18)) *
          FIELD(arg0, s16, 0x1E)) >> 12));

    FIELD(arg1, s32, 0x14) += 0xFFFE0000 +
        ((rand() & 0xFF) << 9);
    FIELD(arg0, s16, 0x18) = (s16)(FIELD(arg0, u16, 0x18) + 0x80 +
        (rand() & 0x3F));

    do {
    } while (0);

    x = FIELD(arg0, s32, 0x28) + FIELD(arg0, s32, 0x34);
    FIELD(arg0, s32, 0x28) = x;
    value = FIELD(arg0, s32, 0x1C);
    if (value <= 0) {
        x >>= 2;
    }
    FIELD(arg0, s32, 0x1C) = value + x;

    c0 = FIELD(arg2, u8, 0xC);
    c1 = FIELD(arg2, u8, 0xD);
    FIELD(arg2, u8, 0xC) = c0 - (c0 >> 4);
    FIELD(arg2, u8, 0xD) = c1 - (c1 >> 4);
    c2 = FIELD(arg2, u8, 0xE);
    FIELD(arg2, u8, 0xE) = c2 - (c2 >> 4);
    if (FIELD(arg2, u16, 0x14) & 0x6000) {
        FIELD(arg2, s8, 4) = 0;
        FIELD(arg2, s8, 5) = 0;
    }

    if (FIELD(arg1, s16, 0xA) < FIELD(arg0, s16, 0x10) - 0x60) {
        FIELD(arg0, u16, 0x4C)++;
        func_800D7F1C();
        return;
    }
    return;

state_one:
    {
        u16 *fixed = D_80083460;
        fixed[5]--;
    }
    FIELD(arg0, u16, -2) |= 0x8000;
    D_800814A0 |= 0x8000;
}
