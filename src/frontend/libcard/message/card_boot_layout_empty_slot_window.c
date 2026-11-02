#include "frontend/libcard/display_node.h"
#include "common.h"

#include "modules/main_server_ship_interfaces.h"
#include "engine/audio/sequence.h"
#include "frontend/libcard/message.h"
#include "main/data.h"

/* Initializes resources and screen positions for three display entries. */
void card_boot_layout_empty_slot_window(void *object) {
    CardMenuDisplayNode *display_entry;
    s32 resource_index;

    display_entry = *(CardMenuDisplayNode **)((u8 *) object + 0x260);
    resource_index = (card_boot_get_remaining_block_summary() >= 3);
    display_entry->payload.data = decode_fullwidth_text((u8 *) object + 8, D_800282A4[resource_index], 1);
    display_entry->block->fields.x = 0xF0;
    display_entry->block->fields.y = 0x91;

    display_entry = *(CardMenuDisplayNode **)((u8 *) object + 0x270);
    display_entry->block->fields.x = 0x70;
    display_entry->block->fields.y = 0x10;
    display_entry->payload.data = &D_800791A4;

    display_entry = *(CardMenuDisplayNode **)((u8 *) object + 0x278);
    display_entry->payload.data = (u8 *) object + 0x134;
    display_entry->block->fields.x = 0xAE;
    display_entry->block->fields.y = 0x18;
}
