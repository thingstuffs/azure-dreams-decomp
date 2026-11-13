/* Clear the selection marker and refresh the card slot window. */

#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "frontend/libcard.h"
#include "frontend/libcard/slot_list.h"
#include "shared/object_node.h"

/* Restore the slot window's frame tint and clear its selection marker text. */
void card_boot_clear_slot_selection_marker(void *object_addr) {
    CardSlotWindow *window;

    if (object_addr != 0) {
        window = NODE_BODY(object_addr);
        window->frame_block.fields.unk_00 = 0x606868;
        window->pointers[9]->unk_00 = 0;
    }
}

/* Runs three update routines on the data of a non-null object. */
void card_boot_refresh_slot_window(void *object_addr) {
    void *object_data;

    if (object_addr != 0) {
        object_data = object_addr + 0x20;
        card_boot_release_slot_window_texts(object_data);
        card_boot_clear_ten_display_slots(object_data);
        card_boot_populate_slot_window_display(object_data);
    }
}
