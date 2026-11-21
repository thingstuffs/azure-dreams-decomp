#ifndef FRONTEND_CARD_CHOICE_PANEL_H
#define FRONTEND_CARD_CHOICE_PANEL_H
#include "frontend/libcard/display_node.h"
#include "shared/timed_stream.h"
/* Common pointer-table prefix read by the two-row CARD_DEV initializer. */
typedef struct CardDevChoicePanelPrefix {
    u8 pad_00[0x60];
    CardMenuDisplayNode **children;
} CardDevChoicePanelPrefix;

typedef struct CardDevPairedChoiceData {
    s32 values[2];
    FrameNode *entries[2];
} CardDevPairedChoiceData;

extern CardDevPairedChoiceData card_dev_paired_choice_data;
extern FrameNode card_dev_choice_cursor_data;
#endif
