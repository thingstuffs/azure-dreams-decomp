#include "modules/dungeon_resource03_slot0.h"

void finish_actor_tile_move_and_check_trap(R03_801721C0_S_801721C0_0 *object, void *unused, void *check_data, void *target) {
    if (update_actor_movement_to_tile() != 0) {
        reduce_actor_food_meter(target, 4);
        advance_status_timers(target);
        if ((check_actor_floor_trap(check_data, target) << 0x10) > 0) {
            object->unk_8C = ((void *)func_80170E54);
            if (g_dungeon_status.flags & 0x80) {
                object->unk_90.at02.v = 0;
                object->unk_90.at00.v = 0;
            }
        }
    } else {
        if (g_dungeon_status.flags & 0x80) {
            object->unk_90.at02.v = 0;
            object->unk_90.at00.v = 0;
        }
    }
}
