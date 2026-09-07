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

void func_8191CA88(void *arg0, void *arg1, S_8191CA88_2 *arg2) {
    void *object = arg0;
    S_8191CA88_3 *motion;
    register s32 state ASM_REG("$4");   /* MATCH pin: load-bearing for the whole function shape */
    register s32 state_u ASM_REG("$5");   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    s32 timer;
    register s32 old_timer ASM_REG("$2");   /* MATCH pin: keeps a statement from moving across a call/branch */
    s32 compare_left;
    s32 compare_right;
    s32 compare_result;
    s32 timer_signed;
    s32 threshold_value;
    s32 threshold_result;
    u8 *global_base;
    s32 position;
    s32 acceleration;
    s32 next_state;
    s32 x_velocity;
    s32 y_velocity;
    u16 arg2_field;
    S_8191CA88_1 *inner;

    inner = ((S_8191CA88_0 *)object)->unk_00;
    inner->unk_14 = inner->unk_14 + 1;
    arg2_field = arg2->unk_1A;
    ASM_USE(arg2_field);   /* MATCH pin: retail schedule: same instructions, different order without it */
    motion = arg1;
    ASM_KEEP(motion);   /* MATCH pin: retail schedule: same instructions, different order without it */
    arg2->unk_1A = arg2_field + 0x300;
    old_timer = ((S_8191CA88_0 *)object)->unk_10.s;
    state = ((S_8191CA88_0 *)object)->unk_0E.s;
    ASM_SCHED_BARRIER();   /* MATCH pin: retail schedule: same instructions, different order without it */
    state_u = ((S_8191CA88_0 *)object)->unk_0E.u;
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
        func_800243C4(state, state_u, arg2, object);
    }
    if (state == 2) {
        goto state_2;
    }
    if (state == 3) {
        goto state_3;
    }
    func_800243C4(state, state_u, arg2, object);

state_0:
    position = motion->unk_00;
    acceleration = motion->unk_0C;
    x_velocity = motion->unk_10;
    y_velocity = motion->unk_14;
    motion->unk_00 = position + acceleration;
    motion->unk_04 += x_velocity;
    motion->unk_08 += y_velocity;
    compare_left = ((S_8191CA88_0 *)object)->unk_10.p;
    compare_right = ((S_8191CA88_0 *)object)->unk_14;
    compare_result = compare_left < compare_right;
    ASM_TAILSLOT_PIN_TIED(compare_result);   /* MATCH pin: retail keeps a copy the compiler would otherwise drop/add */
    func_80024388(x_velocity, y_velocity, arg2, object);

state_1:
    timer_signed = timer << 16;
    threshold_value = ((S_8191CA88_0 *)object)->unk_16;
    timer_signed >>= 16;
    threshold_result = timer_signed < threshold_value;
    if (threshold_result != 0) {
        goto done;
    }
    ((S_8191CA88_0 *)object)->unk_0E.s = state_u + 1;
    ((S_8191CA88_0 *)object)->unk_10.u = 0;
    func_800243C4(state, state_u, arg2, object);

state_2:
    motion->unk_08 -= timer << 16;
    if (((S_8191CA88_0 *)object)->unk_10.p < 0x18) {
        goto done;
    }
    next_state = ((S_8191CA88_0 *)object)->unk_0E.p + 1;
    ((S_8191CA88_0 *)object)->unk_10.u = 0;
    ((S_8191CA88_0 *)object)->unk_0E.p = next_state;
    func_800243C4(state, state_u, arg2, object);

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
