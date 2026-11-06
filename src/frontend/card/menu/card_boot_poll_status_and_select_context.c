#include "common.h"
#include "frontend/card/menu.h"
#include "frontend/card/service.h"
#include "main/data.h"
#include "frontend/card.h"
#include "shared/object_node.h"

typedef struct S_80407E64_0 {
    u8 pad_00[0xC];
    s32 unk_0C;
    u8 pad_10[0x1C];
    void * unk_2C;
    u8 pad_30[0x8];
    s32 unk_38;
} S_80407E64_0;   /* arg0 in card_boot_poll_status_and_select_context */

extern void initialize_card_message_object_with_code_0xd(void *context);

/* Polls the status and selects the corresponding context update and data. */
void card_boot_poll_status_and_select_context(void *state_arg) {
    S_80407E64_0 *state = state_arg;
    s32 retry_status;
    s32 status;
    s32 retries;
    ObjectNodeHeader *context;

    retries = 0;
    retry_status = 5;
    do {
        status = card_dev_run_selected_operation(state->unk_0C);
        if (status != retry_status) {
            break;
        }
    } while (retries++ < 6);

    state->unk_38 = 0;
    reset_card_selection_state();
    if (status == 1) {
        context = NODE_HEADER(state);
        state->unk_2C = card_boot_handle_menu_selection_input;
        initialize_card_message_object_with_code_0xd(context);
        context->update_callback = D_80407DB8;
    } else if (status == 4) {
        context = NODE_HEADER(state);
        state->unk_2C = card_boot_handle_menu_selection_input;
        card_dev_show_no_memory_card_notice(context);
        context->update_callback = D_80407D90;
    } else {
        context = NODE_HEADER(state);
        state->unk_2C = card_boot_handle_menu_selection_input;
        card_dev_show_format_failure_notice(context);
        context->update_callback = D_80407DB8;
    }
}
