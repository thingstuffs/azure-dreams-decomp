#include "common.h"
#include "shared/dungeon_status.h"
#include "shared/dir_step.h"

extern s16 get_offset_map_cell_value_and_flags(s16 x, s16 y, s16 offset_index, u16 *flags);
extern s32 sample_terrain_surface_height(s32 x, s32 y, s16 min_height);
extern u16 D_800DCE6C[];
extern u16 D_800DCE8C[];

/* Finds a nearby unblocked position with a distance below 0x200. */
s32 find_valid_floor_item_position(s16 x, s16 y, s16 z, s16 *out_x, s16 *out_y, s16 *out_distance) {
    u16 tile_flags;
    s32 distance;
    s32 i;
    s16 dir;

    if (get_offset_map_cell_value_and_flags(x - 1, y, 0, &tile_flags) != 0 && !(tile_flags & 0x8820)) {
        distance = sample_terrain_surface_height(((x << 6) + 0x20) & 0xFFE0, ((y << 6) + 0x20) & 0xFFE0, z - 0x20);
        if ((s16)distance < 0x200) {
            *out_x = x;
            *out_y = y;
            *out_distance = distance;
            return 1;
        }
    }

    dir = g_dungeon_status.unk_1E & 7;
    for (i = 0; i < 8; i++, dir = (dir + 1) & 7) {
        if (get_offset_map_cell_value_and_flags(x, y, dir, &tile_flags) != 0 && !(tile_flags & 0x8820)) {
            distance = sample_terrain_surface_height((((x + dir_step_x[dir]) << 6) + 0x20) & 0xFFE0,
                (((y + dir_step_y[dir]) << 6) + 0x20) & 0xFFE0, z - 0x20);
            if ((s16)distance < 0x200) {
                *out_x = x + dir_step_x[dir];
                *out_y = y + dir_step_y[dir];
                *out_distance = distance;
                return 1;
            }
        }
    }

    dir = g_dungeon_status.unk_1E & 0xF;
    for (i = 0; i < 0x10; i++, dir = (dir + 1) & 0xF) {
        if (get_offset_map_cell_value_and_flags(x + D_800DCE6C[dir] - 1, y + D_800DCE8C[dir], 0, &tile_flags) != 0 && !(tile_flags & 0x8820)) {
            distance = sample_terrain_surface_height((((x + (s16)D_800DCE6C[dir]) << 6) + 0x20) & 0xFFE0,
                (((y + (s16)D_800DCE8C[dir]) << 6) + 0x20) & 0xFFE0, z - 0x20);
            if ((s16)distance < 0x200) {
                *out_x = x + D_800DCE6C[dir];
                *out_y = y + D_800DCE8C[dir];
                *out_distance = distance;
                return 1;
            }
        }
    }
    return 0;
}
