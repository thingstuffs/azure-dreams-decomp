#ifndef FRONTEND_CARD_SLOT_MARKER_H
#define FRONTEND_CARD_SLOT_MARKER_H
#include "frontend/libcard/display_node.h"
/* Fields observed by the CARD_DEV selection-marker helper. No allocation
 * extent or table stride is inferred from this prefix. */
typedef struct CardDevSlotMarkerPrefix {
    u8 pad_00[0x1C0];
    s32 unk_1C0;
    u8 pad_1C4[0x58];
    CardMenuDisplayNode *marker;
} CardDevSlotMarkerPrefix;
#endif
