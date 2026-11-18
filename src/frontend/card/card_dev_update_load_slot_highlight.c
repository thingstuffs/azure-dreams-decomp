#include "common.h"
#include "shared/widget_views.h"
#include "shared/object_node.h"
#include "frontend/card.h"
#include "frontend/card/load.h"
#include "main/data.h"


/* Process the record data, run the follow-up routine, and set its header pointer. */
void card_dev_update_load_slot_highlight(void *record_data) {
    card_devkit_highlight_selected_load_slot(record_data);
    reset_card_selection_state();
    NODE_HEADER(record_data)->update_callback = handle_menu_selection_input;
}
