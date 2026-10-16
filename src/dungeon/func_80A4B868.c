#include "modules/dungeon_resource06_slot0.h"

void func_80175068(void *entity_data, s32 unused_1, s32 unused_2, void *other_data)
{
    u8 *entity = entity_data;
    u8 *other = other_data;
    s32 kind = 0x17;

    other[0x71] &= 0x7F;
    *(void **)(entity + 0x8C) = ((void *)func_80175068);
    entity[0x9A] = kind;
    entity[0x9B] = 0;
    other[0x6D] = 0;
    if (!(dungeonStatus.flags & 0x2000) && ((func_800A2BDC(other) << 16) == 0)) {
        *(void **)(entity + 0x8C) = 0;
        entity[0x9A] = kind;
        entity[0x9B] = 0;
        (*(s16 *)D_800DCF5E) = 0;
        dungeonStatus.unk_0A++;
    }
}
