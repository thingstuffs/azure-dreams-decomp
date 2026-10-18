#include "common.h"
#include "shared/object_flags.h"
#include "shared/dir_step.h"

extern s16 sample_terrain_surface_height(u16, u16, s16);
extern u16 D_800281F8[];

/* Update position, reduce movement speed, and flag completion when speed runs out. */
void update_speed_damped_effect(void *motion_data, s16 *position)
{
    s16 *motion = motion_data;
    s16 next_speed;
    u16 update_count = D_800281F8[0];
    u16 z = position[5];
    u16 x = position[1];
    u16 y = position[3];

    D_800281F8[0] = update_count + 1;
    if (position[5] < sample_terrain_surface_height(x, y, z + 2)) {
        ((s32 *)position)[0] -= (dir_step_x[motion[27]] * motion[24]) << 11;
        ((s32 *)position)[1] -= (dir_step_y[motion[27]] * motion[24]) << 11;
        ((s32 *)position)[2] += (0xC0 - motion[24]) << 10;
    }

    next_speed = (u16)motion[24] - 8;
    motion[24] = next_speed;
    if ((next_speed << 16) <= 0) {
        ((u16 *)motion)[-1] |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
