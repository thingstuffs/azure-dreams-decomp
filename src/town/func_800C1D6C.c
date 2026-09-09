#include "common.h"

typedef struct S0 {
    char pad0[0x68];
    s16 f68;
    char pad6A[2];
    s16 f6C;
} S0;

typedef struct S1 {
    char pad0[0x1A];
    u16 f1A;
} S1;

typedef struct S80083780 {
    s32 field0;
    s32 field4;
    s32 field8;
} S80083780;

extern S80083780 D_80083780;

extern s32 func_800352FC(s32, s32 *, S1 *);
extern s32 func_800C2AB4(S0 *);
extern void SD_Call(s32);
extern void *D_80089900[];

#ifndef NON_MATCHING
register s32 state ASM_REG("$7");   /* UNRESOLVED C shape (pin): removing it rematerialises a constant retail keeps in a register; the source shape that makes it unnecessary has not been found */
#else
static s32 state;
#endif

/* Updates the object state, position, and timed target adjustments. */
void func_800BF4CC(S0 *self, s32 *position, S1 *target) {
    S0 *object = self;
    s32 y_limit;
    s32 next_value;
    s32 base_y;
    static void *const state_labels[4] = {&&L_CHECK_DISTANCE, &&L_MOVE, &&L_CHECK_STATE, &&L_RAISE_TARGET};

    {
        s32 countdown;

        countdown = (u16)object->f6C;
        base_y = position[1];
        state = object->f68;
        countdown--;
        object->f6C = countdown;
        ASM_KEEP(countdown);   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    }
    next_value = 0x800000;
    y_limit = base_y + next_value;
    ASM_KEEP(base_y);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
    if ((u32)state < 6) {
        goto *D_80089900[state];
    }
    return;

L_CHECK_DISTANCE: {
        register s32 threshold;
        register s32 x_distance;
        s32 target_x;

        x_distance = D_80083780.field0;
        target_x = position[0];
        x_distance -= target_x;
        threshold = 0x3FFFFF;
        ASM_KEEP(threshold);   /* UNRESOLVED C shape (pin): removing it reorders the instructions (same instructions, different order); the source shape that makes it unnecessary has not been found */
        if (x_distance < 0) {
            x_distance = -x_distance;
        }
        threshold = threshold < x_distance;
        if (threshold != 0) {
            return;
        }
        if (func_800352FC(target_x, position, target) == 0) {
            return;
        }
        if (func_800C2AB4(object) == 0) {
            return;
        }
        SD_Call(0x50B);
        next_value = (u16)object->f68;
        threshold = 32;
        object->f6C = threshold;
        goto L_NEXT_STATE;
    }

L_MOVE: {
        s32 below_limit;

        below_limit = D_80083780.field4 < y_limit;
        if (below_limit != 0) {
            D_80083780.field4 += 0x40000;
        }
        next_value = target->f1A - 32;
        goto L_STORE_TARGET;
    }

L_CHECK_STATE:
    if (func_800352FC((s32)self, position, target) != 0) {
        if (func_800C2AB4(object) != 0) {
            goto L_EXIT;
        }
    }
    object->f68 = (object->f68 + 1) % 6;
    return;

L_RAISE_TARGET:
    next_value = target->f1A + 32;
L_STORE_TARGET:
    target->f1A = next_value;
    if (object->f6C > 0) {
        goto L_EXIT;
    }
    next_value = (u16)object->f68;
L_NEXT_STATE:
    object->f68 = next_value + 1;
L_EXIT:
    return;
}
