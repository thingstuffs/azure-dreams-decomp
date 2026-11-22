#include "frontend/card/choice_panel.h"
#include "common.h"
#include "frontend/card.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"


/* Configures two object entries and initializes them with shared data. */
void card_dev_layout_two_rows(CardDevSlotMenu *panel) {
    CardMenuDisplayNode *entry;
    FrameNode *shared_data;

    shared_data = &card_dev_choice_cursor_data;
    entry = &panel->entry_table[2]->display;
    entry->block->fields.x = 0x40;
    entry->block->fields.y = 0x20;
    initialize_scaled_entry_cursor_8004DDBC(&panel->cursors[0], shared_data, &entry->payload.word);

    entry = &panel->entry_table[3]->display;
    entry->block->fields.x = 0xC0;
    entry->block->fields.y = 0x20;
    initialize_scaled_entry_cursor_8004DDBC(&panel->cursors[1], shared_data, &entry->payload.word);
}
