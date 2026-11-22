#include "frontend/card/choice_panel.h"
#include "common.h"
#include "frontend/card.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"


/* Updates two object slots using the selected slot mapping and values. */
void card_dev_update_slot_pair_rows(CardDevSlotMenu *panel) {
    s32 slot;
    u8 (*slot_map)[2];
    s32 *values;
    u8 mapped_slot;
    CardDevSlotEntry *entry;
    s32 *value_dst;
    s32 mapped_value;
    CardDevSlotEntry **slot_entries;
    s32 map_index;

    slot = 0;
    slot_map = D_80408D40;
    values = card_dev_paired_choice_data.values;
    do {
        mapped_slot = slot_map[panel->selection][slot];
        entry = panel->entry_table[mapped_slot + 2];
        if (entry->display.payload.word != 0) {
            initialize_scaled_entry_cursor_8004DDBC(&panel->cursors[mapped_slot],
                          card_dev_paired_choice_data.entries[slot], &entry->display.payload.word);
        }
        mapped_slot = slot_map[panel->selection][slot];
        panel->entry_table[slot]->display.block->words[0] =
            values[mapped_slot];

        slot_entries = &panel->entry_table[slot];
        map_index = panel->selection;
        mapped_slot = slot_map[map_index][slot];
        value_dst = &slot_entries[2]->display.block->words[0];
        mapped_value = values[mapped_slot];
        *value_dst = mapped_value;
        slot++;
    } while (slot < 2);
}
