#include "common.h"
#include "town/menu/target_adjustment.h"
#include "town/menu.h"
#include "shared/sprite_frame_state.h"

/* Decreases the target's 16-bit value at offset 0x18 by four. */
void decrement_sprite_angle_y(struct DoorProjectionChild *unused_child, struct ObjectPosition *unused_position, SpriteFrameState *target) {
    target->angle_y -= 4;
}
