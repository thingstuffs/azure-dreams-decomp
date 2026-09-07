#include "common.h"

#define FIELD(base, type, offset) (*(type *)((u8 *)(base) + (offset)))
typedef unsigned long uptr;

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

s32 func_8009ADB8(void *arg0, void *arg1, s32 arg2, s32 arg3, volatile s32 arg4)
{
    register MapCell *map ASM_REG("$19");
    u8 *map_state;
    s16 height;
    register s32 next_height ASM_REG("$3");
    s32 z;
    s32 direction;
    s32 x;
    s32 y_sum;
    s16 y;
    register MapCell *cell ASM_REG("$3");

    z = arg4;
    map = D_80083160.map;
    map_state = (u8 *)&D_80083160.map;
    direction = (FIELD(arg0, u16, 0x2A) >> 9) & 7;
    if (!(FIELD(arg1, s32, 0x14) & 0x100) ||
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
        (y << FIELD(map_state, s16, 0x14))) * 6) + (uptr)map);
    ASM_KEEP(cell);

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
    ASM_KEEP(next_height);
    if (next_height < 0x200) {
        goto ret_one;
    }

ret_zero:
    return 0;
ret_one:
    return 1;
}
