#ifndef FRONTEND_LIBCARD_SLOT_DETAILS_H
#define FRONTEND_LIBCARD_SLOT_DETAILS_H
#include "common.h"
#include "shared/menu_display.h"

#include "frontend/libcard/display_node.h"

/* Observed detail-panel fields and pointer tables. No full allocation size
 * or stride is inferred from this view. */
typedef struct CardSlotDetails {
    u8 pad_00[0x7C];
    s32 selected_slot;
    s32 mode;
    u8 text_buffers[7][0x180]; /* glyph lists drawn by text_nodes[0..6] */
    u8 pad_B04[0x48];
    CardDetailDisplayNode *text_nodes[7];
    CardDetailDisplayNode *icon_nodes[10];
} CardSlotDetails;
#endif
