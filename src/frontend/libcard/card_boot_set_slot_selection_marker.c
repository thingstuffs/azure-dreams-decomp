#include "common.h"
#include "frontend/libcard.h"
#include "frontend/libcard/slot_list.h"
#include "slus/card_selection_display_data.h"


/* Set the object color, optional display table, and display dimensions. */
void card_boot_set_slot_selection_marker(ObjectNodeHeader *object_addr, s32 enable_table) {
    CardSlotWindow *window;
    MenuDisplayNode *marker;

    if (object_addr != 0) {
        window = NODE_BODY(object_addr);
        marker = window->pointers[9];
        window->frame_block.fields.unk_00 = 0x808080;
        if (enable_table != 0) {
            marker->unk_00 = (s32)(unsigned long)card_selection_display_data;
        } else {
            marker->unk_00 = 0;
        }
        marker->block->fields.x = 0x60;
        marker->block->fields.y = 0x18;
    }
}
