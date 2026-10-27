#include "common.h"
#include "m2c_compat.h"
#include "frontend/libcard.h"



/* Stores two object values and runs the associated update routines. */
void card_boot_set_slot_details_selection(void *object_addr, s32 value_7c, s32 value_80) {
    CardSlotDetails *object_data;

    if (object_addr != 0) {
        object_data = object_addr + 0x20;
        object_data->selected_slot = value_7c;
        object_data->mode = value_80;
        draw_cylindrical(object_data);
        card_boot_refresh_slot_details(object_data);
    }
}
