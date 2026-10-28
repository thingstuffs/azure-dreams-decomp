#include "common.h"
#include "frontend/card.h"
#include "frontend/libcard/state.h"
#include "frontend/libcard/menu_callbacks.h"
#include "frontend/libcard.h"
#include "main/data.h"


/* Sets up the object from its indexed table entry and assigns its state data. */
void card_boot_confirm_selected_slot_deletion(void *state) {
    void *object = (u8 *)state - 0x20;
    s32 table_index = *(s32 *)((u8 *)state + 0x28);

    if (card_save_slot_metadata[table_index].words[0] != 0) {
        s32 *state_data = &D_80025788;
        void *update_data = (u8 *)state + 0x38;
        *(s32 **)((u8 *)state + 0x34) = state_data;
        card_boot_show_delete_confirmation(object, update_data);
        *(s32 **)((u8 *)state - 0x10) = card_boot_poll_status_and_dismiss_dialog;
    } else {
        *(s32 **)((u8 *)state + 0x34) = build_install;
        card_boot_show_no_saved_game_notice(object);
        *(s32 **)((u8 *)state - 0x10) = card_boot_poll_status_and_dismiss_dialog;
    }

}
