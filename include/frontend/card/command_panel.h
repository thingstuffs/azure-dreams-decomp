#ifndef FRONTEND_CARD_COMMAND_PANEL_H
#define FRONTEND_CARD_COMMAND_PANEL_H
#include "common.h"
#include "frontend/libcard/display_node.h"
/* CARD_DEV's four-row panel has a distinct pointer-table layout. */
typedef struct CardDevCommandPanel {
    u8 pad_00[4];
    u8 highlight_packets[0x78];
    u8 pad_7C[4];
    s32 unk_80;
    s32 unk_84;
    u8 pad_88[8];
    u8 labels[4][0x3C];
    u8 pad_180[0x38];
    CardMenuDisplayNode *marker;
    CardMenuDisplayNode *resource_entry;
    CardMenuDisplayNode *left[4];
    CardMenuDisplayNode *right[4];
    CardMenuDisplayNode *middle[4];
    CardMenuDisplayNode *lower[4];
} CardDevCommandPanel;
#endif
