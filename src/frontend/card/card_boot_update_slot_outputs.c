#include "frontend/card/choice_panel.h"
#include "common.h"
#include "frontend/card.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"

extern void update_two_slots_using_selection_mapping(void *ptr);

/* Updates or clears selected slot outputs, then refreshes the state if any were selected. */
void card_boot_update_slot_outputs(void *state, s32 *enabled, s32 *selected) {
    s32 slot;
    s32 updated;
    s32 data_offset;
    u8 *record;
    CardMenuDisplayNode **output_table;
    CardMenuDisplayNode *output;

    updated = 0;
    slot = 0;
    record = state;
    data_offset = 4;
    do {
        if (selected[slot] != 0) {
            output_table = ((CardDevChoicePanelPrefix *)state)->children;
            output = output_table[slot + 2];
            updated = 1;
            if (enabled[slot] != 0) {
                func_8004DDBC((u8 *)state + data_offset, D_80408A30, output);
            } else {
                output->payload.word = 0;
                *(s32 *)(record + 8) = 0;
            }
        }
        record += 0xC;
        data_offset += 0xC;
        slot++;
    } while (slot < 2);

    if (updated != 0) {
        update_two_slots_using_selection_mapping(state);
    }
}
