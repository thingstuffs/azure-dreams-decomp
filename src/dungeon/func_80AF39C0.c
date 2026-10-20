#include "modules/dungeon_resource10_slot0.h"

void func_801751C0(void *entity_data, s32 unused_1, s32 unused_2, void *other_data)
{
    u8 *entity = entity_data;
    u8 *other_entity = other_data;
    s32 kind = 0x18;

    other_entity[0x71] &= 0x7F;
    *(void **)(entity + 0x8C) = ((void *)func_801751C0);
    entity[0x9A] = kind;
    entity[0x9B] = 0;
    other_entity[0x6D] = 0;
    if (!(g_dungeon_status.flags & 0x2000) && ((has_pending_dungeon_activity(other_entity) << 16) == 0)) {
        *(void **)(entity + 0x8C) = 0;
        entity[0x9A] = kind;
        entity[0x9B] = 0;
        (*(s16 *)D_800DCF5E) = 0;
        g_dungeon_status.activity_counts.parts.pending_action_count++;
    }
}
