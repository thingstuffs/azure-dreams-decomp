#include "common.h"
#include "shared/widget_views.h"
#include "shared/object_node.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "frontend/card/save.h"
#include "main/data.h"


/* Process the record data, run the follow-up routine, and set its header pointer. */
void card_dev_update_save_slot_selection(void *record_data) {
    card_devkit_refresh_save_slot_selection(record_data);
    reset_card_selection_state();
    NODE_HEADER(record_data)->update_callback = handle_object_menu_input;
}
