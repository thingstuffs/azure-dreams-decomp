#include "common.h"
#include "frontend/card/save_operation.h"
#include "shared/object_node.h"
#include "m2c_compat.h"
#include "frontend/card/save.h"
#include "main/data.h"

/* Refreshes the save slot selection and returns the node's callback to handle_object_menu_input. */
void refresh_save_slot_selection_and_resume_menu_input(CardSaveOperationBody *menu) {
    card_devkit_refresh_save_slot_selection(menu);
    NODE_HEADER(menu)->update_callback = handle_object_menu_input;
}
