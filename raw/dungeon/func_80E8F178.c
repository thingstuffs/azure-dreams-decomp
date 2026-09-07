#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))

extern void func_800A7A7C(s16, s16, s16, s32, void *);
extern s32 D_800814A0;

void func_80174978(void *arg0, void *arg1, void *arg2) {
    s32 state;
    register s32 delta ASM_REG("$4");
    register s32 value ASM_REG("$2");
    register s32 sum ASM_REG("$3");
    u16 timer;
    u16 next;

    state = FIELD(arg0, u8, 0x9B);
    if (state == 1) {
        goto state_one;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_zero;
        }
        goto done;
    }
    if (state == 2) {
        goto state_two;
    }
    goto done;

state_zero:
    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u8, 0x9B) = 2;
        goto done;
    }
    FIELD(arg0, u16, 0x96) = 12;
    FIELD(arg0, u8, 0x9B) = FIELD(arg0, u8, 0x9B) + 1;

state_one: {
    s32 left;
    s32 right;

    left = FIELD(arg0, s16, 0xA8) << 6;
    right = FIELD(arg1, s16, 2) - 0x20;
    FIELD(arg1, s16, 2) = (u16)FIELD(arg1, s16, 2) +
        ((left - right) >> 1);
}
    delta = FIELD(arg0, s16, 0xAA);
    value = FIELD(arg1, s32, 0x14) + 0x30000;
    sum = FIELD(arg1, s32, 8) + value;
    FIELD(arg1, s32, 0x14) = value;
    value = FIELD(arg1, s16, 6);
    delta <<= 6;
    FIELD(arg1, s32, 8) = sum;
    value -= 0x20;
    delta -= value;
    delta >>= 1;
    FIELD(arg1, s16, 6) = (u16)FIELD(arg1, s16, 6) + delta;
    if (FIELD(arg2, u16, 0x1C) < 0x1000U) {
        next = FIELD(arg2, u16, 0x1E) + 0x50;
        FIELD(arg2, u16, 0x1E) = next;
        FIELD(arg2, u16, 0x1C) = next;
    }
    timer = FIELD(arg0, u16, 0x96) - 1;
    FIELD(arg0, u16, 0x96) = timer;
    if ((timer << 16) != 0) {
        goto done;
    }
    FIELD(arg1, s32, 0x14) = 0;
    FIELD(arg0, u8, 0x9B) = FIELD(arg0, u8, 0x9B) + 1;
    goto done;

state_two:
    func_800A7A7C(FIELD(arg0, s16, 0xA8),
                  FIELD(arg0, s16, 0xAA),
                  (s16)(FIELD(arg1, u16, 0xA) - 0x20),
                  FIELD(arg2, s32, 8), arg0 + 0x48);
    FIELD(arg0, u16, -2) |= 0x8000;
    D_800814A0 |= 0x8000;

done:
    return;
}
