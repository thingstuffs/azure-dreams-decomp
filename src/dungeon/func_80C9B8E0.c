#include "modules/dungeon_ovl_cb9000.h"

void update_hop_to_tile_and_complete(CL_CB9000_801730E0_S_801730E0_0 *state, EntityRec *motion, Rec_D_80082E80 *action, EntityRec *entity) {
    s16 phase;
    u16 ticks_left;
    s16 wait_ticks;
    u8 *next_script;

    phase = state->unk_9B;
    switch (phase) {
    case 0:
        apply_clamped_actor_value_delta(entity);
        motion->unk_10 = 0;
        motion->unk_0C = 0;
        emit_scattered_effects_unless_blocked(motion);
        emit_scattered_effects_unless_blocked(motion);
        emit_scattered_effects_unless_blocked(motion);
        emit_scattered_effects_unless_blocked(motion);
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
            begin_actor_display_action(state, motion, action, &D_8016F2E4);
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
            begin_actor_display_action(state, motion, action, &D_8016F2E4);
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
        set_record_integer_tile_center(motion, action->unk_24, action->unk_25);
        if (((s32)g_dungeon_status.unk_10) == ((u8 *)entity - 0x20)) {
            g_dungeon_status.unk_10 = ((s32)g_dungeon_status.unk_10) & 0x7FFFFFFF;
        }
        next_script = func_8016B02C;
        state->unk_8C = next_script;
        return;
    }
}
