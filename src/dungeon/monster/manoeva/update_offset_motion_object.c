#include "common.h"
#include "shared/entity.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"
#include "dungeon/monster/manoeva.h"
#include "dungeon/monster/manoeva/offset_motion_object.h"


/* Advance motion and rotation, update facing, and flag the object when its timer expires. */
void update_offset_motion_object(void *object_arg, ObjectPosition *motion_data, void *rotation_arg)
{
    OffsetMotionObjectBody *object = object_arg;
    ObjectPosition *motion = motion_data;
    s32 facing;
    s32 accel_x;
    s32 velocity_y;
    s32 next_velocity_y;
    s32 velocity_x;
    u16 ticks_left;
    SpriteFrameState *rotation = rotation_arg;

    motion->x.v += motion->velocity_x;
    motion->y.v += motion->velocity_y;
    motion->z.v += motion->velocity_z;
    velocity_x = motion->velocity_x;
    accel_x = velocity_x >> 5;
    velocity_y = motion->velocity_y;
    next_velocity_y = velocity_y;
    motion->velocity_x = velocity_x + accel_x;
    next_velocity_y += next_velocity_y >> 5;
    motion->velocity_y = next_velocity_y;
    ticks_left = object->remaining_ticks - 1;
    object->remaining_ticks = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        NODE_HEADER(object)->flags |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
    rotation->scale_x += 0x80;
    rotation->scale_y += 0x80;
    rotation->angle_z += 0x40;
    {
        u16 facing_test;

        facing = ((((s32)(g_game_work.view.camera_rotation.parts.viewAngle + *object->facing_source + 0x100) >> 9) & 7) + 2) << 9;
        facing_test = facing;
        rotation->angle_y = facing;
        if ((facing_test == 0x400) || (facing_test == 0xC00)) {
            rotation->angle_y = facing + 0x100;
        }
    }
}
