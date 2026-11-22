#include "common.h"
#include "frontend/card/menu.h"
#include "frontend/card/service.h"
#include "main/data.h"
#include "frontend/card.h"
#include "shared/object_node.h"


/* Polls the status and selects the corresponding context update and data. */
void card_boot_poll_status_and_select_context(CardChooserBody *state) {
    s32 retry_status;
    s32 status;
    s32 retries;
    ObjectNodeHeader *context;

    retries = 0;
    retry_status = 5;
    do {
        status = card_dev_run_selected_operation(state->selected_channel);
        if (status != retry_status) {
            break;
        }
    } while (retries++ < 6);

    state->wait_notice_state = 0;
    reset_card_selection_state();
    if (status == 1) {
        context = NODE_HEADER(state);
        state->resume_input = card_boot_handle_menu_selection_input;
        initialize_card_message_object_with_code_0xd(context);
        context->update_callback = D_80407DB8;
    } else if (status == 4) {
        context = NODE_HEADER(state);
        state->resume_input = card_boot_handle_menu_selection_input;
        card_dev_show_no_memory_card_notice(context);
        context->update_callback = D_80407D90;
    } else {
        context = NODE_HEADER(state);
        state->resume_input = card_boot_handle_menu_selection_input;
        card_dev_show_format_failure_notice(context);
        context->update_callback = D_80407DB8;
    }
}
