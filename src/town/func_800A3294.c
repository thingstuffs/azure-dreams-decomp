#include "common.h"

extern void *func_800A0988(s32);
extern void *D_800A08F0;

typedef struct {
    s8 pad[0x50];
    void *unk50;
    s8 pad2[0x18];
    s16 unk6C;
} EntityStruct;

/* door_open_demo_set_sub: Set the door opening demo handler and angle. */
void door_open_demo_set_sub(s32 door_id, s16 demo_angle) {
    void *door_object;
    EntityStruct *door;

    door_object = func_800A0988(door_id);
    door = (EntityStruct *)((u8 *)door_object + 0x20);
    if (door_object != 0) {
        door->unk50 = &D_800A08F0;
        door->unk6C = demo_angle;
    }
}
