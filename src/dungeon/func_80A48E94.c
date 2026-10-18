#include "modules/dungeon_resource06_slot0.h"

void func_80172694(void *state, s32 unused, s32 source, s32 target) {
    if (update_actor_movement_to_tile() != 0) {
        reduce_actor_food_meter(target, 4);
        advance_status_timers(target);
        if ((check_actor_floor_trap(source, target) << 16) > 0) {
            *(s32 **)((u8 *)state + 0x8C) = ((s32 *)initialize_destination_state);
            if (g_dungeon_status.flags & 0x80) {
                *(s16 *)((u8 *)state + 0x92) = -0x20;
            }
        }
    } else if (g_dungeon_status.flags & 0x80) {
        *(s16 *)((u8 *)state + 0x92) = -0x20;
    }
}
