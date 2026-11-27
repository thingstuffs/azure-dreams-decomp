#ifndef FRONTEND_CARD_MESSAGE_DISPLAY_H
#define FRONTEND_CARD_MESSAGE_DISPLAY_H
#include "frontend/libcard/display_node.h"
/* The message object links six display nodes and initializes four text rows.
 * The six blocks end at +0x764, the size cleared when the dialog is reused. */
typedef struct CardDevDialogDisplay {
    s32 selection;
    u8 pad_04[4];
    s32 layout_index;
    s32 mode;
    s32 repeat_ticks;
    struct ObjectNodeHeader *owner;
    s32 width;
    s32 height;
    s32 *result_slot;
    u8 command_buffer[0x120];
    u8 pad_144[0xF0];
    u8 text_buffers[4][0x108];
    MenuDisplayBlock primary;
    DisplayPositionWords secondary;
    DisplayPositionWords settings;
    MenuDisplayNode template_node;
    MenuDisplayNode *entries[6];
    MenuDisplayNode display_nodes[6];
    MenuDisplayBlock blocks[6];
} CardDevDialogDisplay;
#endif
