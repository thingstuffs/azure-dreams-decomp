#include "common.h"
#include "shared/entity.h"
#include "shared/game_work.h"
#include "shared/object_flags.h"


typedef struct S_80175C60_1 {
    s16 * unk_00;
    u8 pad_04[0x1C];
    u16 unk_20;
} S_80175C60_1;   /* arg0 in update_offset_motion_object */

typedef struct S_80175C60_2 {
    u8 pad_00[0x18];
    s16 unk_18;
    u16 unk_1A;
    u16 unk_1C;
    u16 unk_1E;
} S_80175C60_2;   /* arg2 in update_offset_motion_object */


/* Advance motion and rotation, update facing, and flag the object when its timer expires. */
void update_offset_motion_object(void *object_arg, void *motion_data, void *rotation_arg)
{
    S_80175C60_1 *object = object_arg;
    ObjectPosition *motion = motion_data;
    s32 facing;
    s32 accel_x;
    s32 velocity_y;
    s32 next_velocity_y;
    s32 velocity_x;
    u16 ticks_left;
    S_80175C60_2 *rotation = rotation_arg;

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
    ticks_left = object->unk_20 - 1;
    object->unk_20 = ticks_left;
    if ((ticks_left << 0x10) <= 0) {
        (*(u16 *)((u8 *)object + -2)) |= NODE_REMOVE;
        object_flag_block.flags |= OBJECT_REMOVE_PENDING;
        return;
    }
    rotation->unk_1C += 0x80;
    rotation->unk_1E += 0x80;
    rotation->unk_1A += 0x40;
    {
        u16 facing_test;

        facing = ((((s32)(g_game_work.view.camera_rotation.parts.viewAngle + *object->unk_00 + 0x100) >> 9) & 7) + 2) << 9;
        facing_test = facing;
        rotation->unk_18 = facing;
        if ((facing_test == 0x400) || (facing_test == 0xC00)) {
            rotation->unk_18 = facing + 0x100;
        }
    }
}
