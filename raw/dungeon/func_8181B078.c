#include "common.h"

#define FIELD(ptr, type, offset) (*(type *)((u8 *)(ptr) + (offset)))

extern s16 D_80025914;
extern s32 D_800814A0[3];

extern void func_8002491C(void) __attribute__((noreturn));
extern void func_80024920(void) __attribute__((noreturn));

void func_8181B078(void *arg0, void *arg1, void *arg2)
{
    s32 one;
    register s32 tail_value ASM_REG("$2");
    s16 state;

    D_80025914 = 1;
    FIELD(arg0, u16, 2)--;

    if (++FIELD(arg0, s16, 0x1C) >= 2) {
        FIELD(arg0, s16, 0x1C) = 0;
        state = FIELD(arg0, s16, 0x1E);
        one = 1;

        if (state == one) {
            goto state_1;
        }
        if (state >= 2) {
            goto check_state_2;
        }
        if (state == 0) {
            goto state_0;
        }
        func_80024920();

check_state_2:
        ASM_SCHED_BARRIER();
        if (state == 2) {
            goto state_2;
        }
        func_80024920();

state_0:
        FIELD(arg0, s16, 0x1E) = one;
        tail_value = FIELD(arg0, u8, 0x28) + 8;
        ASM_TAILSLOT_PIN_TIED(tail_value);
        func_8002491C();

state_1:
        FIELD(arg0, s16, 0x1E) = 2;
        tail_value = FIELD(arg0, u8, 0x28) + 8;
        ASM_TAILSLOT_PIN_TIED(tail_value);
        func_8002491C();

state_2:
        FIELD(arg0, s16, 0x1E) = 0;
        FIELD(arg0, u8, 0x28) -= 16;
    }

    FIELD(arg1, s32, 8) += FIELD(arg0, s32, 0x60);

    if (FIELD(arg0, s16, 2) <= 0) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }

    if (FIELD(arg2, u16, 0x14) & 0x8000) {
        FIELD(arg0, u16, -2) |= 0x8000;
        D_800814A0[0] |= 0x8000;
    }
}
