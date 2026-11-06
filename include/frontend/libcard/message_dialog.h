#ifndef FRONTEND_LIBCARD_MESSAGE_DIALOG_H
#define FRONTEND_LIBCARD_MESSAGE_DIALOG_H
#include "common.h"
#include "shared/menu_display.h"
#include "frontend/libcard/display_node.h"
/* Shared storage initialized by card_boot_create_or_reset_message_dialog for
 * every message-dialog kind. The owner is a node header; the result is a
 * status word that the input handler writes through. */
typedef struct CardMessageDialogBody {
    s32 selected_choice;
    u8 pad_04[4];
    s32 entry_index;
    s32 mode;
    s32 repeat_delay;
    struct ObjectNodeHeader *owner;
    s32 width;
    s32 height;
    s32 *result;
    u8 window_packets[0xC0];
    u8 marker_packet[0x30];
    u8 text_buffers[5][0x180];
    u8 pad_894[0x1C];
    DisplayPositionWords vector;
    u8 display_data[0xC];
    struct S_800491F4 *chain;
    CardMenuDisplayNode *entries[7];
    MenuDisplayNode nodes[7];
    MenuDisplayBlock blocks[7];
} CardMessageDialogBody;
#endif
