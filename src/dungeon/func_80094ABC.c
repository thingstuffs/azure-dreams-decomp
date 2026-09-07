#include "common.h"

typedef struct {
    s16 unk0;
    u16 unk2;
    u16 flags;
} MapCell;

typedef struct {
    u8 pad0[0x1DC];
    MapCell *map;
    u8 pad1E0[0x10];
    s16 mapShift;
} DungeonState;

extern DungeonState D_80083160;

void func_8009A21C(s16 x, s16 y, u16 flags)
{
    DungeonState *state = &D_80083160;
    MapCell *cell;
    u16 value;
    u16 result;

    cell = &state->map[x + (y << state->mapShift)];
    if (flags & 0xC832) {
        result = cell->flags | flags;
        goto store;
    }

    value = ((cell->flags & flags) + (flags & 0x1100)) & 0x3300;
    cell->flags &= ~flags;
    if (value == 0) {
        if (flags == 0x300) {
            value = 0x300;
        } else {
            value = 0x3000;
        }
    }

    result = cell->flags | value;

store:
    cell->flags = result;
}
