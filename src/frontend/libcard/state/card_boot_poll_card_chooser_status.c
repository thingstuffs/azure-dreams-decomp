#include "shared/object_node.h"
#include "common.h"
#include "shared/game_work.h"

#include "modules/main_server_ship_interfaces.h"
#include "frontend/libcard.h"
#include "frontend/libcard/state.h"
#include "main/data.h"

/* Updates the selected callback or triggers a one-time action when no callback is selected. */
void card_boot_poll_card_chooser_status(CardChooserBody *state) {
    s32 callback_index;
    void (*callback)(CardChooserBody *);

    if ((g_game_work.buttons != 0) && ((g_game_work.pressed_buttons) & 0x20)) {
        card_boot_toggle_channel();
        state->wait_notice_state = 0;
        (NODE_HEADER(state))->update_callback = card_boot_update_card_chooser_input;
        return;
    }

    callback_index = card_boot_debounce_card_status_events();
    no_op_card_stub();
    if (callback_index != 0) {
        state->wait_notice_state = 0;
        state->slot_status = callback_index;
        callback = D_8002809C[callback_index];
        state->unk_34 = callback_index;
        (NODE_HEADER(state))->update_callback = callback;
        return;
    }

    if ((card_boot_get_operation_state() == 3) && (state->wait_notice_state == 0)) {
        card_boot_show_please_wait_notice(NODE_HEADER(state), &state->wait_notice_state);
        state->wait_notice_state = 1;
    }
}
