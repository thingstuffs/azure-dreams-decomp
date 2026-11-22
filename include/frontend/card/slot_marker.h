#ifndef FRONTEND_CARD_SLOT_MARKER_H
#define FRONTEND_CARD_SLOT_MARKER_H
#include "shared/object_node.h"
#include "frontend/card/server_menu.h"
/* A devkit card slot window: the 0x20-byte node header and its CardDevMenu10 body. */
typedef struct CardDevSlotWindow {
    ObjectNodeHeader node;
    CardDevMenu10 body;
} CardDevSlotWindow;

void card_dev_initialize_slot_window(CardDevMenu10 *window, struct ObjectNodeHeader *owner, s32 slot_index);
#endif
