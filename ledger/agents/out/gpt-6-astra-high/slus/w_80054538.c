#include "common.h"

#ifndef NULL
#define NULL 0
#endif

/* Sibling struct (matches src/code.c's S_800848F8 and src/w_800544A4.c's
 * S_80084858 field-for-field): no-arg completion callback at 0x0, s32
 * counter at 0x4, s16 pair at 0x8/0xA, state at 0xC, then the s16 fields
 * this function ramps (0x10 current value, 0x12 clamp target, 0x14 step). */
typedef struct S_80054538 {
    /* 0x00 */ void (*field0)(void);
    /* 0x04 */ s32 field4;
    /* 0x08 */ s16 field8;
    /* 0x0A */ s16 fieldA;
    /* 0x0C */ s32 state;
    /* 0x10 */ s16 field10;
    /* 0x12 */ s16 field12;
    /* 0x14 */ s16 field14;
    /* 0x16 */ s16 field16;
    /* 0x18 */ s16 field18;
} S_80054538;

/* Advances the active ramp, clamps its value at the limit, and invokes its callback. */
void func_80054538(S_80054538 *ramp) {
    s16 next_value;
    s16 target;
    void (*callback)(void);

    switch (ramp->state) {
    case 1:
        next_value = ramp->field10 + ramp->field14;
        ramp->field10 = next_value;
        if (next_value >= 0x80) {
            ramp->field10 = 0x7F;
            ramp->state = 3;
        }
        break;
    case 2:
        next_value = ramp->field10 - ramp->field14;
        target = ramp->field12;
        ramp->field10 = next_value;
        if (next_value < ramp->field12) {
            ramp->field10 = target;
            ramp->state = 3;
        }
        break;
    default:
        return;
    }

    callback = ramp->field0;
    if (callback != NULL) {
        callback();
    }
}
