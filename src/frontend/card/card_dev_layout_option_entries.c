#include "common.h"
#include "frontend/card/slot_marker.h"
#include "frontend/card.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"


/* Initializes three object entries with data pointers and attribute values. */
void card_dev_layout_option_entries(CardDevMenu10 *window) {
    CardDevMenuEntry *entry;

    entry = window->entries[6];
    entry->display.block->fields.x = 0x100;
    entry->display.block->fields.y = 0x10;
    entry->display.payload.data = &D_80084110;

    entry = window->entries[3];
    entry->display.payload.data = (void *) func_80051B50(window->option_text, &D_804005F0, 1);
    entry->display.block->fields.x = 0x181;
    entry->display.block->fields.y = 0x91;

    entry = window->entries[8];
    entry->display.payload.data = window->option_packets;
    entry->display.block->fields.x = 0x112;
    entry->display.block->fields.y = 0x18;
}
