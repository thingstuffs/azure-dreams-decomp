#include "common.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"

typedef unsigned long uptr;

typedef struct S_8009ADB8_0 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_8009ADB8_0;   /* arg0 in can_push_adjacent_actor */

typedef struct S_8009ADB8_1 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8009ADB8_1;   /* arg1 in can_push_adjacent_actor */

typedef struct S_8009ADB8_2 {
    u8 pad_00[0x14];
    s16 unk_14;
} S_8009ADB8_2;   /* map_state in can_push_adjacent_actor */


typedef struct {
    u16 type;
    u16 unk2;
    u16 flags;
} FacingMapCell;

extern s32 sample_terrain_surface_height(s32 x, s32 y, s16 min_height);

/* Checks the facing cell for valid terrain flags and an acceptable height. */
s32 can_push_adjacent_actor(S_8009ADB8_0 *facing_state, S_8009ADB8_1 *attributes, s16 tile_x, s16 tile_y,
    s16 initial_height)
{
    FacingMapCell *map;
    u8 *map_state;
    s16 height;
    s32 next_height;
    s32 direction;
    s16 next_x;
    s16 next_y_sum;
    s16 next_y;
    FacingMapCell *next_cell;

    map = ((FacingMapCell *)g_game_work.map.cells);
    map_state = (u8 *)((FacingMapCell * *)&g_game_work.map.cells);
    direction = (facing_state->unk_2A >> 9) & 7;
    if (!(attributes->unk_14 & 0x100) ||
        (height = sample_terrain_surface_height(
             (((tile_x << 16) >> 10) + 0x20) & 0xFFE0,
             (((tile_y << 16) >> 10) + 0x20) & 0xFFE0,
             initial_height),
         height >= 0x200)) {
        return 0;
    }

    next_x = tile_x + ((u16 *)dir_step_x)[direction];
    next_y_sum = tile_y + ((u16 *)dir_step_y)[direction];
    next_y = (s16)next_y_sum;
    next_cell = (FacingMapCell *)((uptr)((s16)(next_x +
        (next_y << ((S_8009ADB8_2 *)map_state)->unk_14)) * 6) + (uptr)map);

    if (!(next_cell->flags & 0xB300)) {
        if (next_cell->type != 0) {
            next_height = sample_terrain_surface_height(
                (((next_x << 16) >> 10) + 0x20) & 0xFFE0,
                ((next_y << 6) + 0x20) & 0xFFE0,
                height) << 16;
            next_height >>= 16;
            if (next_height < 0x200) {
                return 1;
            }
        }
    }
    return 0;
    return 1;
}
