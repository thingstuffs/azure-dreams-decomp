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
    void *value;
    MainPosition *position;
} MainEntry;

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
                                     card_menu_entry_values[*(s32 *)((u8 *)context + 8)].words[entry_index], 1);
    }
}
