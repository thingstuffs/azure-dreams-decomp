#include "common.h"
#include "shared/dungeon_status.h"

typedef struct {
    u8 pad0[2];
    u16 flags;
    u8 pad4[6];
    u16 count;
} DungeonState;

extern s32 func_800A2BDC(void *arg0);
extern s16 D_800DCF5E;
extern u8 D_801751C0[12];

/* Initializes entity state and conditionally clears its data pointer and increments the dungeon count. */
void func_801751C0(void *entity_data, s32 unused_1, s32 unused_2, void *other_data)
{
    u8 *entity = entity_data;
    u8 *other_entity = other_data;
    s32 kind = 0x18;

    other_entity[0x71] &= 0x7F;
    *(void **)(entity + 0x8C) = &D_801751C0;
    entity[0x9A] = kind;
    entity[0x9B] = 0;
    other_entity[0x6D] = 0;
    if (!(dungeonStatus.flags & 0x2000) && ((func_800A2BDC(other_entity) << 16) == 0)) {
        *(void **)(entity + 0x8C) = 0;
        entity[0x9A] = kind;
        entity[0x9B] = 0;
        D_800DCF5E = 0;
        dungeonStatus.unk_0A++;
    }
}
