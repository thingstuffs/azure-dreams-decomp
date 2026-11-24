#include "common.h"
#include "shared/object_node.h"
#include "frontend/libcard/format_operation.h"
#include "frontend/libcard/state.h"
#include "frontend/libcard.h"

/* Card status 3: ask whether to format the card; the answer handler resumes afterwards. */
void card_boot_enter_format_confirmation(CardChooserBody *state) {
    state->resume_input = card_boot_handle_format_answer;
    card_boot_show_format_confirmation(NODE_HEADER(state), &state->format_answer);
    NODE_HEADER(state)->update_callback = card_boot_poll_status_and_dismiss_dialog;
}
