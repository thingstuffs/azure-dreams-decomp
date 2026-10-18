#include "modules/town_door.h"

/* into_dn_door_demo_set: Initialize the dungeon entrance door demo state and handler. */
void into_dn_door_demo_set(void) {
    void *door_object;
    S_800A0A88_0 *door;

    door_object = find_door_keyed_node(&D_800D4404);
    door = (void *)((u8 *)door_object + 0x20);
    if (door_object != 0) {
        door->unk_90 = 6;
        door->unk_50 = &update_door_completion_state;
    }
}
