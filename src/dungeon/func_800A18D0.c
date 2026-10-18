#include "modules/dungeon_engine_entity_effects_storage.h"
#include "shared/dungeon_item_entries.h"
#include "common.h"

typedef struct {
    u8 unk0;
    u8 unk1;
    u8 pad[10];
} Entry;


extern void update_map_cell_flags_with_item_limit(u8, u8, s32);

/* Clear active entries at the target coordinates and update their map tile. */
void remove_floor_items_at_tile(s16 target_x, s16 target_y) {
    Entry *entry;
    s32 *entry_state;
    s32 entry_index;
    s32 x;
    s32 y;
    u8 entry_x;
    u8 entry_y;

    entry_index = 0;
    x = target_x;
    y = target_y;
    entry_state = ((s32 *)D_800E3548);
    entry = ((Entry *)D_800E36C8);
    do {
        if (((u8 *) entry_state)[1] != 0) {
            entry_x = entry->unk0;
            if (entry_x == x) {
                entry_y = entry->unk1;
                if (entry_y == y) {
                    *entry_state = 0;
                    update_map_cell_flags_with_item_limit(entry_x, entry_y, 0x800);
                }
            }
        }
        entry_state++;
        entry_index++;
        entry++;
    } while (entry_index < 0x40);
}
