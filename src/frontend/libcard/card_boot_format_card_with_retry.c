#include "common.h"
#include "frontend/libcard/format_operation.h"
#include "frontend/libcard/state.h"



#include "modules/main_server_ship_interfaces.h"
#include "frontend/libcard.h"
#include "main/data.h"

/* Polls status with bounded retries and dispatches the corresponding context update. */
void card_boot_format_card_with_retry(void *state_arg) {
    CardFormatOperationBody *state = state_arg;
    s32 retry_status;
    s32 status;
    s32 retry_count;
    void *context;

    retry_count = 0;
    retry_status = 5;
    do {
        status = card_boot_format_card_and_wait(state->channel);
        if (status != retry_status) {
            break;
        }
    } while (retry_count++ < 6);

    state->notice_state = 0;
    card_boot_recheck_selected_channel();
    if (status == 1) {
        context = NODE_HEADER(state);
        state->resume_callback = card_boot_update_card_chooser_input;
        card_boot_show_format_success_notice(context);
        NODE_HEADER(state)->update_callback = D_800274D8;
    } else if (status == 4) {
        context = NODE_HEADER(state);
        state->resume_callback = card_boot_update_card_chooser_input;
        card_boot_show_no_memory_card_notice(context);
        NODE_HEADER(state)->update_callback = card_boot_restore_chooser_mode;
    } else {
        context = NODE_HEADER(state);
        state->resume_callback = card_boot_update_card_chooser_input;
        card_boot_show_format_failure_notice(context);
        NODE_HEADER(state)->update_callback = D_800274D8;
    }
}
