#include "shared/object_node.h"
#include "common.h"
#include "frontend/libcard/format_operation.h"
#include "frontend/libcard.h"
#include "main/data.h"

/* Checks the object's guard field, initializes its state, and installs its dispatch table. */
void card_boot_handle_format_answer(CardFormatOperationBody *state) {
    void (*handler)(CardChooserBody *);

    if (state->format_answer != 0) {
        handler = card_boot_update_card_chooser_input;
    } else {
        state->format_countdown = 1;
        card_boot_show_formatting_progress(NODE_HEADER(state), &state->wait_notice_state);
        state->wait_notice_state = 1;
        handler = card_boot_wait_before_formatting_card;
    }
    NODE_HEADER(state)->update_callback = handler;
}
