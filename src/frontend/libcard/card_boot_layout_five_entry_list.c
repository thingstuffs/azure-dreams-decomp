#include "common.h"
#include "frontend/libcard/interfaces.h"
#include "engine/audio/sequence.h"
#include "frontend/libcard.h"

typedef struct MainPosition {
    u8 pad0[8];
    s16 x;
    s16 y;
} MainPosition;

typedef struct MainEntry {
    s32 value;
    MainPosition *position;
} MainEntry;

extern s32 D_800280B4[][6];

/* Positions five entries in a vertical list and initializes their values from the selected table. */
void card_boot_layout_five_entry_list(void *context)
{
    s32 entry_index;
    MainEntry *entry;

    for (entry_index = 0; entry_index < 5; entry_index++) {
        entry = ((MainEntry **)((u8 *)context + 0x8CC))[entry_index];
        entry->position->x = 0x124 - (*(s32 *)((u8 *)context + 0x18) / 2);
        entry->position->y = entry_index * 0x11 - (*(s32 *)((u8 *)context + 0x1C) / 2) + 0xFC;
        entry->value = decode_fullwidth_text((u8 *)context + 0x114 + entry_index * 0x180,
                                     D_800280B4[*(s32 *)((u8 *)context + 8)][entry_index], 1);
    }
}
