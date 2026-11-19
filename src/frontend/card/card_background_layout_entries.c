#include "common.h"
#include "frontend/card.h"

/* Initialize seven entries with layout values and pointers into their owner. */
void card_background_layout_entries(CardBackgroundBody *owner) {
    CardDevMenuEntry *entry;
    u8 *shared_data;

    entry = owner->entry_table[0];
    entry->display.block->fields.x = 6;
    entry->display.block->fields.y = 0x10;
    entry->display.payload.data = owner->first_packets;

    entry = owner->entry_table[5];
    entry->display.block->fields.x = 0;
    entry->display.block->fields.y = 0;
    entry->display.payload.data = owner->alternate_packets;

    entry = owner->entry_table[6];
    entry->display.block->fields.x = 0x68;
    entry->display.block->fields.y = 0;
    entry->display.payload.data = owner->selected_packets;

    entry = owner->entry_table[1];
    entry->display.block->fields.x = 0xA0;
    shared_data = owner->shared_packets;
    entry->display.block->fields.y = 0x70;
    entry->display.payload.data = shared_data;

    entry = owner->entry_table[2];
    entry->display.block->fields.x = 0;
    entry->display.block->fields.y = 0x70;
    entry->display.payload.data = shared_data;

    entry = owner->entry_table[3];
    entry->display.block->fields.x = 0xA0;
    entry->display.block->fields.y = 0;
    entry->display.payload.data = shared_data;

    entry = owner->entry_table[4];
    entry->display.block->fields.x = 0;
    entry->display.block->fields.y = 0;
    entry->display.payload.data = shared_data;
}
