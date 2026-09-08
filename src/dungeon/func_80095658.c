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

s32 func_8009ADB8(S_8009ADB8_0 *arg0, S_8009ADB8_1 *arg1, s32 arg2, s32 arg3, volatile s32 arg4)
{
    register MapCell *map ASM_REG("$19");   /* UNRESOLVED C shape (pin): removing it changes the address form (%hi/%lo vs base+offset); the source shape that makes it unnecessary has not been found */
    u8 *map_state;
    s16 height;
    register s32 next_height ASM_REG("$3");   /* UNRESOLVED C shape (pin): removing it changes the whole function shape; the source shape that makes it unnecessary has not been found */
    s32 z;
    s32 direction;
    s32 x;
    s32 y_sum;
    s16 y;
    MapCell *cell;

    z = arg4;
    map = D_80083160.map;
    map_state = (u8 *)&D_80083160.map;
    direction = (arg0->unk_2A >> 9) & 7;
    if (!(arg1->unk_14 & 0x100) ||
        (height = func_800BCB04(
             (((arg2 << 16) >> 10) + 0x20) & 0xFFE0,
             (((arg3 << 16) >> 10) + 0x20) & 0xFFE0,
             (s16)z),
         height >= 0x200)) {
        return 0;
    }

    x = arg2 + D_8006CCD8[direction];
    y_sum = arg3 + D_8006CCE8[direction];
    y = (s16)y_sum;
    cell = (MapCell *)((uptr)((s16)(x +
        (y << ((S_8009ADB8_2 *)map_state)->unk_14)) * 6) + (uptr)map);

    if (cell->flags & 0xB300) {
        goto ret_zero;
    }
    if (cell->type == 0) {
        goto ret_zero;
    }
    next_height = func_800BCB04(
        (((x << 16) >> 10) + 0x20) & 0xFFE0,
        ((y << 6) + 0x20) & 0xFFE0,
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
