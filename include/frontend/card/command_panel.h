#ifndef FRONTEND_CARD_COMMAND_PANEL_H
#define FRONTEND_CARD_COMMAND_PANEL_H
#include "common.h"
#include "frontend/libcard/display_node.h"
/* CARD_DEV's four-row panel has a distinct pointer-table layout. */
typedef struct CardDevCommandPanel {
    u8 pad_00[0x80];
    s32 unk_80;
    s32 unk_84;
    u8 pad_88[0x130];
    CardMenuDisplayNode *marker;
    u8 pad_1BC[4];
    CardMenuDisplayNode *left[4];
    CardMenuDisplayNode *right[4];
    CardMenuDisplayNode *middle[4];
    CardMenuDisplayNode *lower[4];
} CardDevCommandPanel;
#endif
