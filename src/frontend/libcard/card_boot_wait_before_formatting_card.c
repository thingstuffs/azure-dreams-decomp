#include "common.h"
#include "frontend/libcard/format_operation.h"
#include "m2c_compat.h"
#include "frontend/libcard.h"
#include "main/data.h"



/* Decrement the record's countdown and switch its handler when it becomes negative. */
void card_boot_wait_before_formatting_card(CardFormatOperationBody *state) {
    s32 countdown;

    countdown = state->format_countdown - 1;
    state->format_countdown = countdown;
    if (countdown < 0) {
        NODE_HEADER(state)->update_callback = card_boot_format_card_with_retry;
    }
}
