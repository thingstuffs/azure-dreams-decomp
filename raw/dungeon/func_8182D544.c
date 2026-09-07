#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

extern void func_80024E80(void) __attribute__((noreturn));
extern void func_8004491C();
extern void func_800478B8(void *);
extern s32 rand(void);
extern u8 D_80045340[0x10];
extern s32 D_800814A0[3];

void func_8182D544(void *arg0, void *arg1, void *arg2)
{
    s16 state;
    s32 delta_y;
    s32 delta_z;
    s32 amount;
    u16 timer;
    u8 value;
    void *object;

    object = FIELD(arg0, void *, 0);
    FIELD(object, s32, 0xC) |= 0x8000;

    delta_y = FIELD(arg1, s32, 0x10);
    delta_z = FIELD(arg1, s32, 0x14);
    FIELD(arg1, s32, 0) += FIELD(arg1, s32, 0xC);
    FIELD(arg1, s32, 4) += delta_y;
    FIELD(arg1, s32, 8) += delta_z;

    state = FIELD(arg0, s16, 0x4C);
    if (state == 0) {
        goto state_zero;
    }
    if (state == 1) {
        goto state_one;
    }
    func_80024E80();

state_zero:
    timer = FIELD(arg0, u16, 0x48) - 1;
    FIELD(arg0, u16, 0x48) = timer;
    if ((timer << 16) <= 0) {
        func_8004491C((u8 *)arg0 - 0x20, D_80045340, delta_z);
        FIELD(arg0, u16, 0x4C)++;
        func_80024E80();
    }
    return;

state_one:
    func_800478B8(arg2);
    if (FIELD(arg2, u16, 0x14) & 0x6000) {
        FIELD(arg2, s8, 4) = 0;
        FIELD(arg2, s8, 5) = 0;
    }

    amount = (rand() & 0xF) + 9;
    if (amount >= FIELD(arg2, u8, 0xC)) {
        FIELD(arg2, s32, 0xC) = 0;
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
        func_80024E80();
        return;
    }

    value = FIELD(arg2, u8, 0xE) - amount;
    FIELD(arg2, u8, 0xE) = value;
    FIELD(arg2, u8, 0xD) = value;
    FIELD(arg2, u8, 0xC) = value;
}
