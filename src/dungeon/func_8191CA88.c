#include "common.h"

typedef struct S_8191CA88_0_pre {
    u16 unk_00;
} S_8191CA88_0_pre;   /* the 0x2 bytes before object in func_8191CA88, addressed as object[-1] */

typedef struct S_8191CA88_0 {
    void * unk_00;
    u8 pad_04[0xA];
    union { s16 s; volatile u16 u; u16 p; } unk_0E;   /* accessed as both */
    union { volatile u16 s; u16 u; s16 p; } unk_10;   /* accessed as both */
    u8 pad_12[0x2];
    s16 unk_14;
    s16 unk_16;
} S_8191CA88_0;   /* object in func_8191CA88 */

typedef struct S_8191CA88_1 {
    u8 pad_00[0x14];
    u16 unk_14;
} S_8191CA88_1;   /* inner in func_8191CA88 */

typedef struct S_8191CA88_2 {
    u8 pad_00[0x1A];
    u16 unk_1A;
} S_8191CA88_2;   /* arg2 in func_8191CA88 */

typedef struct S_8191CA88_3 {
    s32 unk_00;
    s32 unk_04;
    s32 unk_08;
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_8191CA88_3;   /* motion in func_8191CA88 */

typedef struct S_8191CA88_4 {
    u8 pad_00[0x14A0];
    u32 unk_14A0;
} S_8191CA88_4;   /* global_base in func_8191CA88 */





/* Updates object motion and timers through movement, waiting, falling, and completion states. */
void func_8191CA88(void *object, S_8191CA88_3 *motion, S_8191CA88_2 *effect) {
    s32 state;
    u16 state_unsigned;
    s32 timer;
    u16 old_timer;
    s32 move_timer;
    s32 move_duration;
    s32 moving;
    s32 signed_timer;
    s32 wait_duration;
    s32 waiting;
    u8 *global_base;
    s32 x_position;
    s32 x_velocity;
    s16 next_state;
    s32 y_velocity;
    s32 z_velocity;
    u16 phase;
    S_8191CA88_1 *inner;

    inner = ((S_8191CA88_0 *)object)->unk_00;
    inner->unk_14 = inner->unk_14 + 1;
    phase = effect->unk_1A;
    effect->unk_1A = phase + 0x300;
    old_timer = ((S_8191CA88_0 *)object)->unk_10.s;
    state = ((S_8191CA88_0 *)object)->unk_0E.s;
    state_unsigned = ((S_8191CA88_0 *)object)->unk_0E.u;
    timer = old_timer + 1;
    ((S_8191CA88_0 *)object)->unk_10.u = timer;

    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        return;
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    goto done;

state_0:
    x_position = motion->unk_00;
    x_velocity = motion->unk_0C;
    y_velocity = motion->unk_10;
    z_velocity = motion->unk_14;
    motion->unk_00 = x_position + x_velocity;
    motion->unk_04 += y_velocity;
    motion->unk_08 += z_velocity;
    move_timer = ((S_8191CA88_0 *)object)->unk_10.p;
    move_duration = ((S_8191CA88_0 *)object)->unk_14;
    if (move_timer < move_duration) goto done;
    next_state = ((S_8191CA88_0 *)object)->unk_0E.p + 1;
    ((S_8191CA88_0 *)object)->unk_10.u = 0;
    ((S_8191CA88_0 *)object)->unk_0E.p = next_state;
    goto done;

state_1:
    signed_timer = timer << 16;
    wait_duration = ((S_8191CA88_0 *)object)->unk_16;
    signed_timer >>= 16;
    waiting = signed_timer < wait_duration;
    if (waiting != 0) {
        goto done;
    }
    ((S_8191CA88_0 *)object)->unk_0E.s = state_unsigned + 1;
    ((S_8191CA88_0 *)object)->unk_10.u = 0;
    goto done;

state_2:
    motion->unk_08 -= timer << 16;
    if (((S_8191CA88_0 *)object)->unk_10.p < 0x18) {
        goto done;
    }
    next_state = ((S_8191CA88_0 *)object)->unk_0E.p + 1;
    ((S_8191CA88_0 *)object)->unk_10.u = 0;
    ((S_8191CA88_0 *)object)->unk_0E.p = next_state;
    goto done;

state_3:
    ((S_8191CA88_0_pre *)object)[-1].unk_00 |= 0x8000;
    global_base = (u8 *)0x80080000;
    ((S_8191CA88_4 *)global_base)->unk_14A0 |= 0x8000;

done:
    return;
}

