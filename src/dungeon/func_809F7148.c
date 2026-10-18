#include "common.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad0[2];
    u16 flags;
    u8 pad4[6];
    u16 count;
} DungeonState;

extern s32 has_pending_dungeon_activity(void *other);
extern s16 D_800DCF5E;
extern u8 D_80174948[12];

/* Initializes entity state and conditionally increments the dungeon count. */
void initialize_counted_entity_action(void *entity_data, s32 unused_1, s32 unused_2, void *other_data)
{
    u8 *entity = entity_data;
    u8 *other = other_data;
    s32 kind = 0x17;

    other[0x71] &= 0x7F;
    *(void **)(entity + 0x8C) = &D_80174948;
    entity[0x9A] = kind;
    entity[0x9B] = 0;
    other[0x6D] = 0;
    if (!(g_dungeon_status.flags & 0x2000) && ((has_pending_dungeon_activity(other) << 16) == 0)) {
        *(void **)(entity + 0x8C) = 0;
        entity[0x9A] = kind;
        entity[0x9B] = 0;
        D_800DCF5E = 0;
        g_dungeon_status.unk_0A++;
    }
}
