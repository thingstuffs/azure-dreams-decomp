#include "common.h"
#include "frontend/card/save_operation.h"
#include "shared/object_node.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "frontend/card/save.h"
#include "main/data.h"


/* Process the record data, run the follow-up routine, and set its header pointer. */
void card_dev_update_save_slot_selection(CardSaveOperationBody *menu) {
    card_devkit_refresh_save_slot_selection(menu);
    reset_card_selection_state();
    NODE_HEADER(menu)->update_callback = handle_object_menu_input;
}
