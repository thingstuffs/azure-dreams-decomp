#include "common.h"
#include "shared/object_node.h"

#include "modules/main_server_ship_interfaces.h"
#include "frontend/card.h"
#include "frontend/libcard.h"

/* Updates object pointers and processes five entries when its status check succeeds. */
void card_boot_apply_slot_deletion_response(CardSlotMenuState *object) {
    s32 entry_index;

    if (object->dialog_response != 0) {
        NODE_HEADER(object)->update_callback = card_boot_handle_slot_selection_input;
        return;
    }

    if (card_boot_erase_slot_file(object->selected_slot) != 0) {
        NODE_HEADER(object)->update_callback = card_boot_handle_slot_selection_input;
        entry_index = 0;
        do {
            card_boot_refresh_slot_window(object->slots[entry_index]);
            entry_index++;
        } while (entry_index < 5);
    } else {
        object->saved_callback = card_boot_handle_slot_selection_input;
        card_boot_show_delete_failure_notice(NODE_HEADER(object));
        NODE_HEADER(object)->update_callback = card_boot_restore_saved_selection_callback;
    }

    card_boot_recheck_selected_channel();
    object->progress_dialog_active = 0;
}
