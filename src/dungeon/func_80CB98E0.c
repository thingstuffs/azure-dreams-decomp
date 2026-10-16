#include "modules/dungeon_ovl_cd7000.h"

void func_8014F0E0(CL_CD7000_801730E0_S_801730E0_0 *state, EntityRec *motion, Rec_D_80082E80 *action, EntityRec *entity) {
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
            func_800AAA54(state, motion, action, &D_801512E4);
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
            func_800AAA54(state, motion, action, &D_801512E4);
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
        next_script = func_8014D02C;
        state->unk_8C = next_script;
        return;
    }
}
