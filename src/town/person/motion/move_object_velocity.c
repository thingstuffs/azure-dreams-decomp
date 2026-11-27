#include "common.h"
#include "town/player.h"
#include "town/person.h"
#include "town/person/motion.h"

extern s32 falling_object_xy_velocity[2];

/* Moves the object by its velocity and switches callbacks when vertical velocity is nonnegative. */
void move_object_velocity(OwnerCallbackObject *owner, ObjectPosition *position, SpriteFrameState *unused_output)
{
    s32 *velocity;
    s32 velocity_z;

    velocity = falling_object_xy_velocity;
    velocity_z = position->velocity_z;
    position->x.v += velocity[0];
    position->y.v += velocity[1];
    position->z.v += velocity_z;
    add_vertical_gravity(position);
    if (position->velocity_z >= 0) {
        owner->callback = &step_falling_object;
    }
}
