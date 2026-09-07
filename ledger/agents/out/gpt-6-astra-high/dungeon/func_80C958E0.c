#include "common.h"
#include "m2c_compat.h"

typedef struct S_801730E0_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801730E0_0;   /* arg0 in func_801730E0 */

typedef struct S_801730E0_1 {
    u8 pad_00[0xC];
    s32 unk_0C;
    s32 unk_10;
    s32 unk_14;
} S_801730E0_1;   /* arg1 in func_801730E0 */

typedef struct S_801730E0_2 {
    u8 pad_00[0x1C];
    s32 unk_1C;
    u8 pad_20[0x8];
    u8 unk_28;
} S_801730E0_2;   /* arg3 in func_801730E0 */

typedef struct S_801730E0_3 {
    u8 pad_00[0x14];
    u16 unk_14;
    u8 pad_16[0xE];
    u8 unk_24;
    u8 unk_25;
} S_801730E0_3;   /* arg2 in func_801730E0 */


extern s32 D_80083460[3];
extern u8 D_8017102C[];
extern M2C_UNK D_801752E4;
extern void func_800A2B04(void *, u8, u8);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);
extern void func_800B66C8(void *);
extern void func_800419EC(s32, s32);

/* Advance the action wait states, then reset motion and switch scripts. */
void func_801730E0(S_801730E0_0 *state, S_801730E0_1 *motion, S_801730E0_3 *action, void *entity) {
    s16 phase;
    u16 ticks_left;
    s16 wait_ticks;
    s32 *entity_slots;
    u8 *next_script;

    phase = state->unk_9B;
    if (phase == 1)
        goto wait_action;
    if (phase < 2) {
        if (phase == 0)
            goto start_action;
        goto done;
    }
    if (phase == 2)
        goto finish_action;
    goto done;

start_action:
        func_800AD4D0(entity);
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800B66C8(motion);
        func_800B66C8(motion);
        func_800B66C8(motion);
        func_800B66C8(motion);
        func_800419EC(4, 6);
        state->unk_9B = state->unk_9B + 1;
        if (((S_801730E0_2 *)entity)->unk_28 != 0) {
            if (action->unk_14 & 0x8000) {
                state->unk_96.s = 0;
                state->unk_9B = 2;
                goto done;
            }
            wait_ticks = -1U;
            if (((S_801730E0_2 *)entity)->unk_1C & 0x228)
                wait_ticks = 8;
            state->unk_96.s = wait_ticks;
            goto update_wait;
        }
        motion->unk_14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800AAA54(state, motion, action, &D_801752E4);
        goto done;

wait_action:
update_wait:
        if (state->unk_96.u > 0) {
            ticks_left = state->unk_96.s - 1;
            state->unk_96.s = ticks_left;
            goto check_wait;
        }
        if (action->unk_14 & 0x6000)
            state->unk_96.s = 0;
check_wait:
        if (state->unk_96.u != 0)
            goto done;
        if (((S_801730E0_2 *)entity)->unk_28 == 0) {
            motion->unk_14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800AAA54(state, motion, action, &D_801752E4);
            goto done;
        }
        func_800419EC(1, 1);
        state->unk_96.s = 8;
        state->unk_9B = state->unk_9B + 1;
        goto done;

finish_action:
        ticks_left = state->unk_96.s - 1;
        state->unk_96.s = ticks_left;
        if ((ticks_left << 0x10) > 0)
            goto done;
        motion->unk_14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, action->unk_24, action->unk_25);
        entity_slots = D_80083460;
        if (entity_slots[4] == (entity - 0x20)) {
            entity_slots[4] = entity_slots[4] & 0x7FFFFFFF;
        }
        next_script = D_8017102C;
        state->unk_8C = next_script;
        goto done;

done:
    return;
}
