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



extern void func_80024388() __attribute__((noreturn));
extern void func_800243C4() __attribute__((noreturn));

/* Updates object motion and timers through movement, waiting, falling, and completion states. */
void func_8191CA88(void *object_data, void *motion_data, S_8191CA88_2 *effect) {
    void *object = object_data;
    S_8191CA88_3 *motion;
    register s32 state ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 state_unsigned ASM_REG("$5");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 timer;
    register s32 old_timer ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 move_timer;
    s32 move_duration;
    s32 moving;
    s32 signed_timer;
    s32 wait_duration;
    s32 waiting;
    u8 *global_base;
    s32 x_position;
    s32 x_velocity;
    s32 next_state;
    s32 y_velocity;
    s32 z_velocity;
    u16 phase;
    S_8191CA88_1 *inner;

    inner = ((S_8191CA88_0 *)object)->unk_00;
    inner->unk_14 = inner->unk_14 + 1;
    phase = effect->unk_1A;
    ASM_USE(phase);   /* MATCH pin: retail schedule: same instructions, different order without it */
    motion = motion_data;
    ASM_KEEP(motion);   /* MATCH pin: retail schedule: same instructions, different order without it */
    effect->unk_1A = phase + 0x300;
    old_timer = ((S_8191CA88_0 *)object)->unk_10.s;
    state = ((S_8191CA88_0 *)object)->unk_0E.s;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    state_unsigned = ((S_8191CA88_0 *)object)->unk_0E.u;
    ASM_USE(old_timer);   /* MATCH pin: retail schedule: same instructions, different order without it */
    timer = old_timer + 1;
    ((S_8191CA88_0 *)object)->unk_10.u = timer;

    if (state == 1) {
        goto state_1;
    }
    if (state < 2) {
        if (state == 0) {
            goto state_0;
        }
        func_800243C4(state, state_unsigned, effect, object);
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    func_800243C4(state, state_unsigned, effect, object);

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
    moving = move_timer < move_duration;
    ASM_TAILSLOT_PIN_TIED(moving);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    func_80024388(y_velocity, z_velocity, effect, object);

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
    func_800243C4(state, state_unsigned, effect, object);

state_2:
    motion->unk_08 -= timer << 16;
    if (((S_8191CA88_0 *)object)->unk_10.p < 0x18) {
        goto done;
    }
    next_state = ((S_8191CA88_0 *)object)->unk_0E.p + 1;
    ((S_8191CA88_0 *)object)->unk_10.u = 0;
    ((S_8191CA88_0 *)object)->unk_0E.p = next_state;
    func_800243C4(state, state_unsigned, effect, object);

state_3:
    ((S_8191CA88_0_pre *)object)[-1].unk_00 |= 0x8000;
    global_base = (u8 *)0x80080000;
    ASM_KEEP(global_base);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    ((S_8191CA88_4 *)global_base)->unk_14A0 |= 0x8000;

done:
    return;
}

/* MECHANISM: Noreturn tails plus path-local $a0/$a1/$a3/$t0 carriers let LEAD 18/19 elide the false frame.
   Load-order seams and a held $v1 page base preserve the retail timer/state/global access schedule.
   Explicit sll/lh/sra staging and the tied $v0 tail-slot comparison close the final code-motion residue. */
