#include "modules/dungeon_ovl_18ee800.h"
#include "common.h"
#include "shared/object_flags.h"


extern s32 rand(void);

/* Raises the source toward its height limit and flags the object when its counter expires. */
void func_8002428C(void *object_data, void *source_data)
{
    u8 *object = object_data;
    u8 *source = source_data;
    u16 x;
    u16 y;
    u16 z;
    u16 probe_z;
    s32 height_limit;
    s32 random_value;

    z = *(u16 *)(source + 0xA);
    x = *(u16 *)(source + 2);
    y = *(u16 *)(source + 6);
    probe_z = z + 2;
    D_80025924[0] = 1;
    height_limit = sample_terrain_surface_height(x, y, (s16)probe_z);
    if (*(s16 *)(source + 0xA) < height_limit) {
        random_value = rand();
        *(u32 *)(source + 8) += 0x20000 + (random_value & 0xFFF);
    }

    *(s16 *)(object + 0x32) -= 8;
    if (*(s16 *)(object + 0x32) <= 0) {
        *(u16 *)(object - 2) |= 0x8000;
        object_flag_block.flags |= 0x8000;
    }
}
