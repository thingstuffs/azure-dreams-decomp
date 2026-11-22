#include "common.h"
#include "shared/widget_views.h"
#include "shared/object_node.h"
#include "frontend/card.h"
#include "frontend/card/load.h"
#include "main/data.h"


/* Process the record data, run the follow-up routine, and set its header pointer. */
void card_dev_update_load_slot_highlight(CardDevLoadSlotScreen *screen) {
    card_devkit_highlight_selected_load_slot(screen);
    reset_card_selection_state();
    NODE_HEADER(screen)->update_callback = handle_menu_selection_input;
}
