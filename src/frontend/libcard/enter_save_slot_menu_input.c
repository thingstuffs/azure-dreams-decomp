#include "shared/object_node.h"
#include "main.h"
#include "frontend/libcard/message.h"
#include "common.h"
#include "shared/widget_views.h"
#include "m2c_compat.h"
#include "frontend/libcard.h"
#include "frontend/libcard/resource.h"


/* Update the record, run the shared follow-up, and install its next table. */
void enter_save_slot_menu_input(void *record_data) {
    card_boot_highlight_selected_load_slot(record_data);
    card_boot_recheck_selected_channel();
    ((ObjectNodeHeader *)record_data - 1)->update_callback = card_boot_update_save_slot_menu_input;
}
