#include "common.h"
#include "frontend/libcard.h"
#include "frontend/libcard/resource.h"
#include "main.h"
#include "main/data.h"
#include "frontend/card.h"
#include "shared/object_node.h"

/* Select a state pointer from the operation result and clear the trailing word. */
void card_boot_load_selected_slot(CardSlotMenuState *state) {
    s32 *next_state;
    s32 result;
    ObjectNodeHeader *owner;

    result = card_boot_load_save_and_clear_marker(state->selected_slot, 0x80010000, 1);
    owner = NODE_HEADER(state);
    if (result == 0) {
        next_state = card_boot_handle_slot_selection_input;
        state->saved_callback = next_state;
        card_boot_show_load_failure_notice(owner);
        next_state = (s32 *)0x80020000;
        next_state = card_boot_restore_saved_selection_callback;
    } else {
        no_op_card_hook(0x80010000);
        next_state = card_boot_finish_slot_load_and_change_scene;
    }
    NODE_HEADER(state)->update_callback = next_state;
    card_boot_recheck_selected_channel();
    state->progress_dialog_active = 0;
}
