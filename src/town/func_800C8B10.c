#include "common.h"

extern void create_positioned_sprite_object(s32 position, void *state_value, void *graphic_id);
extern u8 D_800C6180[];
extern u8 D_800ED15C[];

/* Creates an object at the given position with preset state and sprite data. */
void create_object_given_position_preset(s32 position) {
    create_positioned_sprite_object(position, D_800C6180, D_800ED15C);
}
