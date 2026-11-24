#include "common.h"
#include "frontend/libcard.h"
#include "frontend/libcard/slot_list.h"
#include "slus/item_menu_primary_page_data.h"

/* Set the slot window colour, its optional marker table and the marker size (0x66 x 0x18):
 * the copy-source marker of card_boot_refresh_copy_slot_markers. */
void card_boot_set_copy_source_marker(ObjectNodeHeader *object_addr, s32 enable_table) {
    CardSlotWindow *window;
    MenuDisplayNode *marker;

    if (object_addr != 0) {
        window = NODE_BODY(object_addr);
        marker = window->pointers[9];
        window->frame_block.fields.unk_00 = 0x808080;
        if (enable_table != 0) {
            /* MenuDisplayNode.unk_00 is an s32 slot holding the marker table address. */
            marker->unk_00 = (s32)(unsigned long)item_menu_primary_page_data;
        } else {
            marker->unk_00 = 0;
        }
        marker->block->fields.x = 0x66;
        marker->block->fields.y = 0x18;
    }
}
