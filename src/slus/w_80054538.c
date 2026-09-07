#include "common.h"

/* Timed-ramp/state-machine step for a task-block struct (same family as
 * src/code.c's S_800848F8 and src/w_800544A4.c's S_80084858): state 1 ramps
 * field10 up by field14, clamping at 0x7F and latching state 3; state 2
 * ramps field10 down by field14, clamping at field12 and latching state 3.
 * Any other state returns immediately without touching anything else. Once
 * a ramp has run, invokes the struct's own no-arg completion callback
 * (field0) if one is set. */
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

void func_80054538(S_80054538 *arg0) {
    s16 v0;
    s16 clamp;
    void (*callback)(void);

    switch (arg0->state) {
    case 1:
        v0 = arg0->field10 + arg0->field14;
        arg0->field10 = v0;
        if (v0 >= 0x80) {
            arg0->field10 = 0x7F;
            arg0->state = 3;
        }
        break;
    case 2:
        v0 = arg0->field10 - arg0->field14;
        clamp = arg0->field12;
        arg0->field10 = v0;
        if (v0 < arg0->field12) {
            arg0->field10 = clamp;
            arg0->state = 3;
        }
        break;
    default:
        return;
    }

    callback = arg0->field0;
    if (callback != NULL) {
        callback();
    }
}
