#include "common.h"

typedef s32 M2C_UNK;

typedef struct DungeonInner {
    u8 pad0[2];
    s16 x;
    u8 pad4[2];
    s16 y;
    u8 pad8[2];
    s16 z;
} DungeonInner;

typedef struct DungeonDescriptor {
    u8 pad0[8];
    DungeonInner *inner;
    u8 padC[4];
    void *field10;
    u8 pad14[0xA4];
    u32 fieldB8;
} DungeonDescriptor;

extern u8 D_80083498[];
extern M2C_UNK D_800A7548;
extern DungeonDescriptor *func_800A8608(u8 *, s32 *, s32, s32, s32);

/* Create a dungeon descriptor centered on the given tile at the specified z coordinate. */
DungeonDescriptor *func_800A7700(s32 tile_x, s32 tile_y, s32 z, s32 *init_data) {
    DungeonDescriptor *descriptor;
    DungeonInner *inner;

    descriptor = func_800A8608(D_80083498, init_data, 0, 0, 0);
    if (descriptor == 0) {
        return 0;
    }
    descriptor->field10 = &D_800A7548;
    inner = descriptor->inner;
    inner->x = (s16)((tile_x << 6) + 0x20);
    inner->y = (s16)((tile_y << 6) + 0x20);
    inner->z = (s16)z;
    descriptor->fieldB8 = *init_data;
    return descriptor;
}
