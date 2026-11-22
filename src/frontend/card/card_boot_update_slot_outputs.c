#include "frontend/card/choice_panel.h"
#include "common.h"
#include "frontend/card.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"


/* Updates or clears selected slot outputs, then refreshes the state if any were selected. */
void card_boot_update_slot_outputs(CardDevSlotMenu *panel, s32 *enabled, s32 *selected) {
    s32 slot;
    s32 updated;
    CardMenuDisplayNode *output;

    updated = 0;
    slot = 0;
    do {
        if (selected[slot] != 0) {
            output = &panel->entry_table[slot + 2]->display;
            updated = 1;
            if (enabled[slot] != 0) {
                initialize_scaled_entry_cursor_8004DDBC(&panel->cursors[slot], &card_dev_choice_cursor_data, &output->payload.word);
            } else {
                output->payload.word = 0;
                panel->cursors[slot].output = 0;
            }
        }
        slot++;
    } while (slot < 2);

    if (updated != 0) {
        update_two_slots_using_selection_mapping(panel);
    }
}
