#include "common.h"
#include "shared/game_work.h"
#include "shared/dir_step.h"

typedef unsigned long uptr;

typedef struct S_8009ADB8_0 {
    u8 pad_00[0x2A];
    u16 unk_2A;
} S_8009ADB8_0;   /* arg0 in func_8009ADB8 */

typedef struct S_8009ADB8_1 {
    u8 pad_00[0x14];
    s32 unk_14;
} S_8009ADB8_1;   /* arg1 in func_8009ADB8 */

typedef struct S_8009ADB8_2 {
    u8 pad_00[0x14];
    s16 unk_14;
} S_8009ADB8_2;   /* map_state in func_8009ADB8 */


typedef struct {
    u16 type;
    u16 unk2;
    u16 flags;
} MapCell;

extern s16 func_800BCB04(s32, s32, s16);

/* Checks the facing cell for valid terrain flags and an acceptable height. */
s32 func_8009ADB8(S_8009ADB8_0 *facing_state, S_8009ADB8_1 *attributes, s16 tile_x, s16 tile_y,
    volatile s32 initial_height)
{
    MapCell *map;
    u8 *map_state;
    s16 height;
    s32 next_height;
    s32 height_hint;
    s32 direction;
    s16 next_x;
    s16 next_y_sum;
    s16 next_y;
    MapCell *next_cell;

    height_hint = initial_height;
    map = ((MapCell *)gameWork.map.cells);
    map_state = (u8 *)((MapCell * *)&gameWork.map.cells);
    direction = (facing_state->unk_2A >> 9) & 7;
    if (!(attributes->unk_14 & 0x100) ||
        (height = func_800BCB04(
             (((tile_x << 16) >> 10) + 0x20) & 0xFFE0,
             (((tile_y << 16) >> 10) + 0x20) & 0xFFE0,
             (s16)height_hint),
         height >= 0x200)) {
        return 0;
    }

    next_x = tile_x + ((u16 *)dirStepX)[direction];
    next_y_sum = tile_y + ((u16 *)dirStepY)[direction];
    next_y = (s16)next_y_sum;
    next_cell = (MapCell *)((uptr)((s16)(next_x +
        (next_y << ((S_8009ADB8_2 *)map_state)->unk_14)) * 6) + (uptr)map);

    if (!(next_cell->flags & 0xB300)) {
        if (next_cell->type != 0) {
            next_height = func_800BCB04(
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
