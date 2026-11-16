#include "common.h"
#include "frontend/libcard.h"
#include "slus/card_selection_display_data.h"


/* Set the object color, optional display table, and display dimensions. */
void card_boot_set_slot_selection_marker(ObjectNodeHeader *object_addr, s32 enable_table) {
    s8 *object_data;
    void *display_data;

    if (object_addr != 0) {
        object_data = NODE_BODY(object_addr);
        display_data = *(void **) (object_data + 0x280);
        *(s32 *) (object_data + 0x224) = 0x808080;
        if (enable_table != 0) {
            *(s32 **) display_data = card_selection_display_data;
        } else {
            *(s32 *) display_data = 0;
        }
        *(s16 *) (*(s8 **) ((s8 *) display_data + 4) + 8) = 0x60;
        *(s16 *) (*(s8 **) ((s8 *) display_data + 4) + 0xA) = 0x18;
    }
}
