#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s16 D_8002694C[5];
extern s32 D_800814A0[3];
extern void func_800256EC(void) __attribute__((noreturn));
extern void func_800256F0(void) __attribute__((noreturn));

void func_8187BE9C(void *arg0, s32 arg1, void *arg2)
{
    s16 state;

    D_8002694C[0] = 1;
    FIELD(arg0, u16, 2)--;

    state = FIELD(arg0, s16, 0x42);
    if (state == 0) {
        goto state_0;
    }
    if (state == 1) {
        goto state_1;
    }
    func_800256F0();

state_0:
    {
        s32 tail_value;

        FIELD(arg0, s16, 0x42) = 1;
        tail_value = FIELD(arg0, u8, 0x4C) + 24;
        ASM_TAILSLOT_PIN_TIED(tail_value);
        func_800256EC();
    }

state_1:
    FIELD(arg0, s16, 0x42) = 0;
    FIELD(arg0, u8, 0x4C) -= 24;
    ASM_SCHED_BARRIER();

    FIELD(arg2, u8, 0xC) =
        FIELD(arg0, u8, 0x36) * FIELD(arg0, s16, 2) /
        FIELD(arg0, s16, 4);
    FIELD(arg2, u8, 0xD) =
        FIELD(arg0, u8, 0x37) * FIELD(arg0, s16, 2) /
        FIELD(arg0, s16, 4);
    FIELD(arg2, u8, 0xE) =
        FIELD(arg0, u8, 0x38) * FIELD(arg0, s16, 2) /
        FIELD(arg0, s16, 4);

    if (FIELD(arg0, s16, 2) <= 0) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }

    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
