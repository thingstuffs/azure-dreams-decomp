#include "common.h"
#include "frontend/card.h"
#include "frontend/libcard/state.h"

#include "modules/main_server_ship_interfaces.h"
#include "frontend/libcard.h"
#include "frontend/libcard/message.h"


/* Selects a record update based on its table entry and status and assigns data pointers. */
void card_boot_prepare_copy_destination_message(CardSlotMenuState *context)
{
    CardSlotMenuState *record;
    void *header_context;
    s32 table_index;
    s32 status;

    record = context;
    table_index = record->selected_slot;
    header_context = NODE_HEADER(record);

    if (card_save_slot_metadata[table_index].words[0] == 0) {
        status = card_boot_get_remaining_block_summary();
        header_context = 0;
        header_context = NODE_HEADER(record);
        if (status < 3) {
            record->saved_callback = card_boot_resume_menu_after_slot_refresh;
            card_boot_show_no_space_card_notice(header_context);
        } else {
            card_boot_enter_copying_progress(record);
            return;
        }
    } else {
        record->saved_callback = card_boot_resume_menu_after_slot_refresh;
        card_boot_show_overwrite_protected_notice(header_context);
    }

    NODE_HEADER(record)->update_callback = card_boot_poll_status_and_dismiss_dialog;
}
