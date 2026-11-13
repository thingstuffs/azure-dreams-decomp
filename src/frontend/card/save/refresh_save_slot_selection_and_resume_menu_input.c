#include "common.h"
#include "shared/widget_views.h"
#include "m2c_compat.h"
#include "frontend/card/save.h"
#include "main/data.h"

/* Refreshes the save slot selection and returns the node's callback to handle_object_menu_input. */
void refresh_save_slot_selection_and_resume_menu_input(void *record_data) {
    card_devkit_refresh_save_slot_selection(record_data);
    ((CardCallbackState *)((u8 *)record_data - 0x10))->callback = handle_object_menu_input;
}
