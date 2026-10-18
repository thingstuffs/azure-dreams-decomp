#include "modules/dungeon_resource07_slot0.h"

void func_801723E0(R07_801723E0_S_801724A8_0 *state, s32 context, s32 source, s32 target) {
    if (update_actor_movement_to_tile(state, context, source, target) != 0) {
        reduce_actor_food_meter(target, 4);
        advance_status_timers(target);
        if ((check_actor_floor_trap(source, target) << 0x10) <= 0) {
            return;
        }
        state->unk_8C = ((void *)func_80170E54);
        state->unk_90.at00.v = 0;
    }
    if (g_dungeon_status.flags & 0x80) {
        state->unk_90.at02.v = 0;
    }
}
