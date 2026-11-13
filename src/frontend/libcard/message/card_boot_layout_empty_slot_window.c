#include "frontend/libcard/display_node.h"
#include "frontend/libcard/slot_list.h"
#include "common.h"

#include "modules/main_server_ship_interfaces.h"
#include "engine/audio/sequence.h"
#include "frontend/libcard/message.h"
#include "main/data.h"

/* Initializes resources and screen positions for three display entries. */
void card_boot_layout_empty_slot_window(CardSlotWindow *object) {
    CardMenuDisplayNode *display_entry;
    s32 resource_index;

    display_entry = (CardMenuDisplayNode *)object->pointers[1];
    resource_index = (card_boot_get_remaining_block_summary() >= 3);
    display_entry->payload.data = decode_fullwidth_text(object->title_glyphs, D_800282A4[resource_index], 1);
    display_entry->block->fields.x = 0xF0;
    display_entry->block->fields.y = 0x91;

    display_entry = (CardMenuDisplayNode *)object->pointers[5];
    display_entry->block->fields.x = 0x70;
    display_entry->block->fields.y = 0x10;
    display_entry->payload.data = &D_800791A4;

    display_entry = (CardMenuDisplayNode *)object->pointers[7];
    display_entry->payload.data = object->wide_panel;
    display_entry->block->fields.x = 0xAE;
    display_entry->block->fields.y = 0x18;
}
