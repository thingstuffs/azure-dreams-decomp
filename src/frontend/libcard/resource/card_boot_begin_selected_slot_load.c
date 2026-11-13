#include "common.h"
#include "frontend/card.h"
#include "frontend/libcard/state.h"
#include "frontend/libcard/menu_callbacks.h"
#include "frontend/libcard.h"
#include "frontend/libcard/resource.h"


/* Selects the parent handler and initializes state based on the indexed table value. */
void card_boot_begin_selected_slot_load(void *state)
{
    CardSlotMenuState *menu = state;
    s32 enabled;
    void *parent;

    parent = NODE_HEADER(state);
    if (card_save_slot_metadata[menu->unk_28].words[0] != 0) {
        enabled = 1;
        menu->countdown = enabled;
        card_boot_show_loading_progress(parent, (u8 *)state + 0x40);
        menu->unk_40 = enabled;
        NODE_HEADER(state)->update_callback = card_boot_wait_before_loading_slot;
    } else {
        menu->saved_callback = card_boot_handle_slot_selection_input;
        card_boot_show_no_saved_game_notice(parent);
        NODE_HEADER(state)->update_callback = card_boot_poll_status_and_dismiss_dialog;
    }
}
