#include "common.h"
#include "town/player.h"
#include "town/person.h"

extern s32 D_800D636C[2];

/* Moves the object by its velocity and switches callbacks when vertical velocity is nonnegative. */
void move_object_velocity(OwnerCallbackObject *owner, ObjectPosition *position, SpriteFrameState *unused_output)
{
    s32 *velocity;
    s32 velocity_z;

    velocity = D_800D636C;
    velocity_z = position->velocity_z;
    position->x.v += velocity[0];
    position->y.v += velocity[1];
    position->z.v += velocity_z;
    add_hex_20000_s_signed_offset_hex_14(position);
    if (position->velocity_z >= 0) {
        owner->callback = &step_falling_object;
    }
}
