#ifndef FRONTEND_CARD_SLOT_DETAILS_H
#define FRONTEND_CARD_SLOT_DETAILS_H

#include "frontend/card/server_menu.h"
#include "shared/object_node.h"

/* The card information constructor clears this 0xDFC-byte body. Four border
 * rows, seven text rows and ten icon rows share its 21-entry display table. */
typedef struct CardDevSlotDetails {
    ObjectNodeHeader *owner;
    u8 border_packets[0x78];
    s32 selected_slot;
    u8 text_buffers[7][0x108];
    u8 pad_7B8[0x318];
    MenuDisplayBlock primary;
    DisplayPositionWords secondary;
    s32 settings[3];
    MenuDisplayNode template_node;
    CardDevMenuEntry *entries[21];
    CardDevMenuEntry nodes[21];
    MenuDisplayBlock blocks[21];
} CardDevSlotDetails;

void initialize_menu_primitive_entries(CardDevSlotDetails *panel, s32 count);
void initialize_menu_item_positions(CardDevSlotDetails *panel);
void initialize_menu_primitive_settings(MenuDisplayNode *node, MenuDisplayBlock *block, DisplayPositionWords *position);
void select_memory_task_exit(CardDevSlotDetails *panel);
s32 register_owner_handler_table(CardDevMenuEntry **entries);

#endif
