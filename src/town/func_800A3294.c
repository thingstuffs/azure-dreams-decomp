#include "modules/town_door.h"

/* door_open_demo_set_sub: Set the door opening demo handler and angle. */
void door_open_demo_set_sub(s32 door_id, s16 demo_angle) {
    void *door_object;
    EntityStruct *door;

    door_object = find_door_keyed_node(door_id);
    door = (EntityStruct *)((u8 *)door_object + 0x20);
    if (door_object != 0) {
        door->unk50 = &advance_door_open_angle;
        door->unk6C = demo_angle;
    }
}
