/* Clear the selection marker and refresh the card slot window. */

#include "common.h"
#include "frontend/libcard.h"
#include "shared/object_node.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "frontend/libcard/slot_list.h"

/* Restore the slot window's frame tint and clear its selection marker text. */
void card_boot_clear_slot_selection_marker(struct ObjectNodeHeader *object) {
    CardSlotWindow *window;

    if (object != 0) {
        window = NODE_BODY(object);
        window->frame_block.fields.unk_00 = 0x606868;
        window->pointers[9]->draw_commands = 0;
    }
}

/* Runs three update routines on the data of a non-null object. */
void card_boot_refresh_slot_window(struct ObjectNodeHeader *object) {
    struct CardSlotWindow *object_data;

    if (object != 0) {
        object_data = NODE_BODY(object);
        card_boot_release_slot_window_texts(object_data);
        card_boot_clear_ten_display_slots(object_data);
        card_boot_populate_slot_window_display(object_data);
    }
}
