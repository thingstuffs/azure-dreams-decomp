#include "shared/object_node.h"
#include "common.h"
#include "shared/widget_views.h"
#include "frontend/libcard.h"
#include "frontend/libcard/resource.h"

/* Decrement the record's countdown and set its pointer when the countdown becomes negative. */
void card_boot_wait_before_loading_slot(Object_800128C8 *record_data) {
    s32 countdown;

    countdown = record_data->countdown - 1;
    record_data->countdown = countdown;
    if (countdown < 0) {
        ((ObjectNodeHeader *)record_data - 1)->update_callback = &card_boot_load_selected_slot;
    }
}
