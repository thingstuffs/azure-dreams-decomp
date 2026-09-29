#include "common.h"
#include "shared/dungeon_status.h"
#include "m2c_compat.h"
#include "shared/entity.h"
#include "records/Rec_D_80082E80.h"

typedef struct S_801730E0_0 {
    u8 pad_00[0x8C];
    u8 * unk_8C;
    u8 pad_90[0x6];
    union { u16 s; s16 u; } unk_96;   /* accessed as both */
    u8 pad_98[0x3];
    u8 unk_9B;
} S_801730E0_0;   /* arg0 in func_801730E0 */





extern u8 D_8017102C[];
extern M2C_UNK D_801752E4;
extern void func_800A2B04(void *, u8, u8);
extern void func_800AAA54(void *, void *, void *, void *);
extern void func_800AD4D0(void *);
extern void func_800B66C8(void *);
extern void func_800419EC(s32, s32);

/* Advance the action wait states, then reset motion and switch scripts. */
void func_801730E0(S_801730E0_0 *state, EntityRec *motion, Rec_D_80082E80 *action, EntityRec *entity) {
    s16 phase;
    u16 ticks_left;
    s16 wait_ticks;
    u8 *next_script;

    phase = state->unk_9B;
    switch (phase) {
    case 0:
        func_800AD4D0(entity);
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800B66C8(motion);
        func_800B66C8(motion);
        func_800B66C8(motion);
        func_800B66C8(motion);
        func_800419EC(4, 6);
        state->unk_9B = state->unk_9B + 1;
        if (entity->unk_28 != 0) {
            if (action->unk_14.at00_u16.v & 0x8000) {
                state->unk_96.s = 0;
                state->unk_9B = 2;
                return;
            }
            wait_ticks = -1U;
            if (entity->flags1C & 0x228)
                wait_ticks = 8;
            state->unk_96.s = wait_ticks;
        } else {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800AAA54(state, motion, action, &D_801752E4);
            return;
        }
    case 1:
        if (state->unk_96.u > 0) {
            ticks_left = state->unk_96.s - 1;
            state->unk_96.s = ticks_left;
        } else {
            if (action->unk_14.at00_u16.v & 0x6000)
                state->unk_96.s = 0;
        }
        if (state->unk_96.u != 0)
            return;
        if (entity->unk_28 == 0) {
            motion->flags14 = 0;
            motion->unk_10 = 0;
            motion->unk_0C = 0;
            func_800AAA54(state, motion, action, &D_801752E4);
            return;
        }
        func_800419EC(1, 1);
        state->unk_96.s = 8;
        state->unk_9B = state->unk_9B + 1;
        return;
    case 2:
        ticks_left = state->unk_96.s - 1;
        state->unk_96.s = ticks_left;
        if ((ticks_left << 0x10) > 0)
            return;
        motion->flags14 = 0;
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        func_800A2B04(motion, action->unk_24, action->unk_25);
        if (((s32)dungeonStatus.unk_10) == ((u8 *)entity - 0x20)) {
            dungeonStatus.unk_10 = ((s32)dungeonStatus.unk_10) & 0x7FFFFFFF;
        }
        next_script = D_8017102C;
        state->unk_8C = next_script;
        return;
    }
}
