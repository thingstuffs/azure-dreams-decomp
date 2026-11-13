#include "common.h"
#include "frontend/card.h"
#include "frontend/libcard/slot_menu.h"
#include "shared/object_node.h"
#include "frontend/libcard/menu_callbacks.h"
#include "main/data.h"
#include "frontend/libcard_callbacks_api.h"
#include "frontend/libcard/state_callbacks_api.h"

extern void card_boot_refresh_copy_slot_markers(void *menu, s32 entry_id);
extern void card_boot_show_no_saved_game_notice(ObjectNodeHeader *object);




/* Select an entry handler and update the owning object's callback. */
void card_boot_select_copy_source_slot(void *state) {
    CardSlotMenuState *menu = state;
    s32 entry_id = menu->unk_28;

    if (card_save_slot_metadata[entry_id].words[0] != 0) {
        menu->unk_2C = entry_id;
        card_boot_refresh_copy_slot_markers(state, entry_id);
        ((ObjectNodeHeader *)state - 1)->update_callback = card_boot_update_copy_destination_selection;
    } else {
        menu->saved_callback = card_boot_handle_slot_selection_input;
        card_boot_show_no_saved_game_notice(NODE_HEADER(state));
        ((ObjectNodeHeader *)state - 1)->update_callback = card_boot_poll_status_and_dismiss_dialog;
    }
}
