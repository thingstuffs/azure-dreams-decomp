#include "common.h"

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

typedef struct {
    u8 pad[0x1DC];
    MapCell *map;
} DungeonState;

extern DungeonState D_80083160;
extern u16 D_8006CCD8[];
extern u16 D_8006CCE8[];
extern s16 func_800BCB04(s32, s32, s16);

/* Checks the facing cell for valid terrain flags and an acceptable height. */
s32 func_8009ADB8(S_8009ADB8_0 *facing_state, S_8009ADB8_1 *attributes, s32 tile_x, s32 tile_y, volatile s32 initial_height)
{
    register MapCell *map ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *map_state;
    s16 height;
    register s32 next_height ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 height_hint;
    s32 direction;
    s32 next_x;
    s32 next_y_sum;
    s16 next_y;
    MapCell *next_cell;

    height_hint = initial_height;
    map = D_80083160.map;
    map_state = (u8 *)&D_80083160.map;
    direction = (facing_state->unk_2A >> 9) & 7;
    if (!(attributes->unk_14 & 0x100) ||
        (height = func_800BCB04(
             (((tile_x << 16) >> 10) + 0x20) & 0xFFE0,
             (((tile_y << 16) >> 10) + 0x20) & 0xFFE0,
             (s16)height_hint),
         height >= 0x200)) {
        return 0;
    }

    next_x = tile_x + D_8006CCD8[direction];
    next_y_sum = tile_y + D_8006CCE8[direction];
    next_y = (s16)next_y_sum;
    next_cell = (MapCell *)((uptr)((s16)(next_x +
        (next_y << ((S_8009ADB8_2 *)map_state)->unk_14)) * 6) + (uptr)map);

    if (next_cell->flags & 0xB300) {
        goto ret_zero;
    }
    if (next_cell->type == 0) {
        goto ret_zero;
    }
    next_height = func_800BCB04(
        (((next_x << 16) >> 10) + 0x20) & 0xFFE0,
        ((next_y << 6) + 0x20) & 0xFFE0,
        height) << 16;
    next_height >>= 16;
    if (next_height < 0x200) {
        goto ret_one;
    }

ret_zero:
    return 0;
ret_one:
    return 1;
}
