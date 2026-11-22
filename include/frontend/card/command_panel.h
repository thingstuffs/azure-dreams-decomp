#ifndef FRONTEND_CARD_COMMAND_PANEL_H
#define FRONTEND_CARD_COMMAND_PANEL_H
#include "common.h"
#include "frontend/libcard/display_node.h"
/* CARD_DEV's four-row panel has a distinct pointer-table layout. */
typedef struct CardDevCommandPanel {
    struct ObjectNodeHeader *owner;
    u8 highlight_packets[0x78];
    u8 row_offsets[4];
    s32 frames;
    s32 frame;
    s32 target_row;
    s32 start_row;
    u8 labels[4][0x3C];
    MenuDisplayBlock primary;
    DisplayPositionWords secondary;
    s32 settings[3];
    MenuDisplayNode template_node;
    CardMenuDisplayNode *marker;
    CardMenuDisplayNode *resource_entry;
    CardMenuDisplayNode *left[4];
    CardMenuDisplayNode *right[4];
    CardMenuDisplayNode *middle[4];
    CardMenuDisplayNode *lower[4];
} CardDevCommandPanel;
#endif
