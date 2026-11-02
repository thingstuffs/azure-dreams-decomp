#ifndef FRONTEND_CARD_MESSAGE_DISPLAY_H
#define FRONTEND_CARD_MESSAGE_DISPLAY_H
#include "frontend/libcard/display_node.h"
/* Only the observed CARD_DEV dialog prefix is described here. Its four
 * 0x108-byte text buffers and node table differ from the libcard dialog. */
typedef struct CardDevDialogDisplay {
    u8 pad_00[8];
    s32 layout_index;
    u8 pad_0C[0xC];
    s32 width;
    s32 height;
    u8 pad_20[0x214];
    u8 text_buffers[4][0x108];
    u8 pad_654[0x38];
    CardMenuDisplayNode *entries[4];
} CardDevDialogDisplay;
#endif
