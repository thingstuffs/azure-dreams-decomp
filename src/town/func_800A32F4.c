#include "modules/town_door.h"

/* door_atari_on_off: Set the collision flag for the selected door. */
void door_atari_on_off(s32 door_id, s16 collision_enabled) {
    S_800A0A54_0 *door;

    door = func_800A0988(door_id);
    if (door != NULL) {
        door->unk_88 = collision_enabled;
    }
}
