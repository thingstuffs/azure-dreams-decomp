#include "common.h"
#include "shared/object_flags.h"
#include "dungeon/level.h"
#include "dungeon/actor/motion.h"


/* Update damped motion with gravity, clamp to the floor, and flag expiration. */
void advance_particle_motion_with_floor_collision(void *object, ObjectPosition *motion) {
    s16 floor_height;
    u16 lifetime;

    floor_height = sample_terrain_surface_height(motion->x.unsigned_parts.integer, motion->y.unsigned_parts.integer, (s16)(motion->z.unsigned_parts.integer + 2));
    if ((s16)motion->z.unsigned_parts.integer < floor_height) {
        motion->x.v += motion->velocity_x;
        motion->y.v += motion->velocity_y;
        motion->z.v += motion->velocity_z;
        motion->velocity_x -= motion->velocity_x >> 2;
        motion->velocity_y -= motion->velocity_y >> 2;
        motion->velocity_z += 0x8000;
    } else {
        motion->z.unsigned_parts.integer = floor_height;
    }
    lifetime = ((u16 *)object)[0x4B] - 8;
    ((u16 *)object)[0x4B] = lifetime;
    if ((lifetime << 16) <= 0) {
        ((u16 *)object)[-1] |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
    }
}
