#include "common.h"

/* Shared gauge/timer struct layout also used by D_800848F8 / D_80084858
 * (see func_8005440C / func_800546B0 / func_800559B4 family notes):
 * field0 (fn ptr), field4 (s32 state), field8 (s16 current value),
 * fieldA (s16 target), field16 (u16 increment step), field18 (u16 decrement step). */
typedef struct S_800545F4 {
    /*0x00*/ void (*field0)(void);
    /*0x04*/ s32 field4;
    /*0x08*/ s16 field8;
    /*0x0A*/ s16 fieldA;
    /*0x0C*/ u8 pad0C[0xA];
    /*0x16*/ u16 field16;
    /*0x18*/ u16 field18;
} S_800545F4;

/*
 * Updates a gauge value toward/away from a target on each tick, based on
 * state (field4): 1 = increasing (clamps at target, sets state to 3 when
 * reached), 2 = decreasing (clamps at 0, returns -1 when depleted without
 * running the completion callback). Any other state is a no-op. On the
 * increasing path, or the decreasing path while still above zero, the
 * completion callback (field0) is invoked if set.
 */
s32 func_800545F4(S_800545F4 *a0)
{
    u16 v0;

    switch (a0->field4) {
    case 1:
        v0 = (u16)(a0->field8 + a0->field16);
        a0->field8 = v0;
        if (a0->fieldA < (s16)v0) {
            a0->field8 = (s16)a0->fieldA;
            a0->field4 = 3;
        }
        break;
    case 2:
        v0 = (u16)(a0->field8 - a0->field18);
        a0->field8 = v0;
        if ((s16)v0 <= 0) {
            a0->field8 = 0;
            return -1;
        }
        break;
    default:
        return 0;
    }

    if (a0->field0 != 0) {
        a0->field0();
    }
    return 0;
}
