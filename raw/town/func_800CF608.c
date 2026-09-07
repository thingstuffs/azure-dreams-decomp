#include "common.h"

#define FIELD(p, type, off) (*(type *)((u8 *)(p) + (off)))

void func_800CCD68(void *arg0)
{
    register s32 value ASM_REG("$2");
    register s32 state ASM_REG("$3");

    state = FIELD(arg0, s16, 0x6A);
    value = 1;
    if (state == value) {
        goto state_1;
    }
    value = state < 2;
    if (value == 0) {
        goto state_ge_2;
    }
    value = 2;
    ASM_KEEP(value);
    value = 0xC00;
    if (state == 0) {
        goto set_value;
    }
    goto done;

state_ge_2:
#ifdef NON_MATCHING
    value = 2;
#endif
    ASM_UNDEF(value);
    if (state == value) {
        goto state_2;
    }
    value = 3;
    if (state == value) {
        goto state_3;
    }
    goto done;

state_1:
    value = --FIELD(arg0, u16, 0x6C);
    if ((value << 16) != 0) {
        goto done;
    }
    value = 0x800;
    FIELD(arg0, u16, 0x72) = value;
    goto advance_state;

state_2:
    value = --FIELD(arg0, u16, 0x6C);
    if ((value << 16) != 0) {
        goto done;
    }
    value = 0x400;
set_value:
    ASM_KEEP(value);
    FIELD(arg0, u16, 0x72) = value;
advance_state:
    value = FIELD(arg0, u16, 0x6A);
    FIELD(arg0, u16, 0x6C) = 3;
    value++;
    FIELD(arg0, u16, 0x6A) = value;
    goto done;

state_3:
    value = --FIELD(arg0, u16, 0x6C);
    if ((value << 16) != 0) {
        goto done;
    }
    value = FIELD(arg0, u16, 0x68);
    FIELD(arg0, u16, 0x72) = 0;
    ASM_KEEP(state);
    FIELD(arg0, u16, 0x6C) = state;
    FIELD(arg0, s16, 0x6A) = 0;
    value++;
    FIELD(arg0, u16, 0x68) = value;
done:
    return;
}

/* MECHANISM: The true-space function is a frameless leaf; both apparent calls are local
   joins, and explicit labels preserve retail block order. Fixed s32 v0/v1 lifetimes,
   a delay-slot keep, and output-only ASM_UNDEF prevent the final beqz fold; NON_MATCHING
   initializes that delay-carried value portably. */
