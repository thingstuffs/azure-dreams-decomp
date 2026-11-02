#ifndef FRONTEND_CARD_SLOT_DETAILS_H
#define FRONTEND_CARD_SLOT_DETAILS_H
#include "common.h"
#include "frontend/libcard/display_node.h"
/* CARD_DEV's detail panel uses different node offsets from the libcard panel.
 * Only these observed text-buffer and display-table ranges are named. */
typedef struct CardDevSlotDetails {
    u8 pad_00[0x7C];
    s32 selected_slot;
    u8 text_buffers[7][0x108];
    u8 pad_7B8[0x360];
    CardMenuDisplayNode *text_nodes[7];
    CardMenuDisplayNode *icon_nodes[10];
} CardDevSlotDetails;
#endif
