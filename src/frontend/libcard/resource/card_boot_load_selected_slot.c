#include "common.h"
#include "frontend/libcard.h"
#include "frontend/libcard/resource.h"
#include "main.h"
#include "main/data.h"
#include "frontend/card.h"

/* Select a state pointer from the operation result and clear the trailing word. */
void card_boot_load_selected_slot(CardSlotMenuState *state) {
    s32 *next_state;
    s32 result;
    s8 *owner;

    result = card_boot_load_save_and_clear_marker(state->unk_28, 0x80010000, 1);
    owner = ((s8 *)state) - 0x20;
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
    *(s32 **)(((s8 *)state) - 0x10) = next_state;
    card_boot_recheck_selected_channel();
    state->unk_40 = 0;
}
