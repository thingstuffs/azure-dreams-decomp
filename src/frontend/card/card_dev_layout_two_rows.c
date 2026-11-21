#include "frontend/card/choice_panel.h"
#include "common.h"
#include "frontend/card.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"


/* Configures two object entries and initializes them with shared data. */
void card_dev_layout_two_rows(void *object) {
    CardMenuDisplayNode *entry;
    CardDevChoicePanelPrefix *panel;
    FrameNode *shared_data;

    panel = object;
    shared_data = &card_dev_choice_cursor_data;
    entry = panel->children[2];
    entry->block->fields.x = 0x40;
    entry->block->fields.y = 0x20;
    initialize_scaled_entry_cursor_8004DDBC((u8 *)object + 4, shared_data, &entry->payload.word);

    entry = panel->children[3];
    entry->block->fields.x = 0xC0;
    entry->block->fields.y = 0x20;
    initialize_scaled_entry_cursor_8004DDBC((u8 *)object + 0x10, shared_data, &entry->payload.word);
}
