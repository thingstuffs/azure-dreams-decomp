#ifndef FRONTEND_CARD_CHOICE_PANEL_H
#define FRONTEND_CARD_CHOICE_PANEL_H
#include "frontend/libcard/display_node.h"
/* Common pointer-table prefix read by the two-row CARD_DEV initializer. */
typedef struct CardDevChoicePanelPrefix {
    u8 pad_00[0x60];
    CardMenuDisplayNode **children;
} CardDevChoicePanelPrefix;
#endif
