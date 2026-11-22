#include "common.h"
#include "frontend/card/slot_marker.h"
#include "frontend/card.h"
#include "main/data.h"
#include "frontend/card/server_imports.h"
#include "frontend/card/service.h"

/* Initializes data pointers and layout values for three child entries. */
void card_dev_layout_title_entries(CardDevMenu10 *window) {
    CardDevMenuEntry *child;
    s32 resource_index;

    child = window->entries[1];
    resource_index = get_table_entry_by_flag() >= 3;
    child->display.payload.data = (void *) func_80051B50(window->title_text, D_80408CB0[resource_index], 1);
    child->display.block->fields.x = 0xF0;
    child->display.block->fields.y = 0x91;

    child = window->entries[5];
    child->display.block->fields.x = 0x70;
    child->display.block->fields.y = 0x10;
    child->display.payload.data = &D_8008432C;

    child = window->entries[7];
    child->display.payload.data = window->slot_packets;
    child->display.block->fields.x = 0xAE;
    child->display.block->fields.y = 0x18;
}
