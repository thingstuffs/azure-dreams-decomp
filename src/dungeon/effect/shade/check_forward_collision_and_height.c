#include "common.h"
#include "m2c_compat.h"
#include "shared/entity.h"

extern s8 actor_direction_step_pairs[];
s32 check_left_tile_and_center_height(s32, s32, s16);
s16 sample_terrain_surface_height(s32, s32, s16);


typedef struct S_800D5F80_2 {
    s16 unk_00;
    s16 unk_02;
} S_800D5F80_2;

/* Checks whether the position ahead passes the collision and height tests. */
s32 check_forward_collision_and_height(EntityRec *position, EntityRec *orientation) {
    s16 surface_height;
    s32 probe_y;
    s32 probe_x;
    s16 probe_height;
    s32 height;
    void *offset_table;
    S_800D5F80_2 *offset;

    height = position->z.w.i;
    probe_height = height - 0x20;
    offset_table = actor_direction_step_pairs;
    offset = offset_table + ((((u16)orientation->facing) >> 7) & 0x1C);
    probe_x = (position->x.w.i + (offset->unk_00 << 6)) & 0xFFFF;
    probe_y = (position->y.w.i + (offset->unk_02 << 6)) & 0xFFFF;
    if ((check_left_tile_and_center_height(probe_x, probe_y, probe_height) << 0x10) == 0) {
        surface_height = sample_terrain_surface_height(probe_x, probe_y, probe_height);
        if (!(surface_height < 0x200 &&
              (position->z.w.i - 0x40) < surface_height)) {
            return 1;
        }
    } else {
        return 1;
    }
    return 0;
}
