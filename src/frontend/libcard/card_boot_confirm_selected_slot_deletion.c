#include "common.h"
#include "frontend/card.h"
#include "frontend/libcard/state.h"
#include "frontend/libcard/menu_callbacks.h"
#include "frontend/libcard.h"
#include "main/data.h"


/* Sets up the object from its indexed table entry and assigns its state data. */
void card_boot_confirm_selected_slot_deletion(CardSlotMenuState *menu) {
    ObjectNodeHeader *object = NODE_HEADER(menu);
    s32 table_index = menu->selected_slot;

    if (card_save_slot_metadata[table_index].words[0] != 0) {
        s32 *state_data = &D_80025788;
        s32 *update_data = &menu->dialog_response;
        menu->saved_callback = state_data;
        card_boot_show_delete_confirmation(object, update_data);
        NODE_HEADER(menu)->update_callback = card_boot_poll_status_and_dismiss_dialog;
    } else {
        menu->saved_callback = card_boot_handle_slot_selection_input;
        card_boot_show_no_saved_game_notice(object);
        NODE_HEADER(menu)->update_callback = card_boot_poll_status_and_dismiss_dialog;
    }

}
