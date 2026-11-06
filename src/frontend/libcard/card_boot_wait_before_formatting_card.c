#include "common.h"
#include "frontend/libcard/format_operation.h"
#include "m2c_compat.h"
#include "frontend/libcard.h"
#include "main/data.h"



/* Decrement the record's countdown and switch its handler when it becomes negative. */
void card_boot_wait_before_formatting_card(void *record_data) {
    CardFormatOperationBody *state = record_data;
    s32 countdown;

    countdown = state->countdown - 1;
    state->countdown = countdown;
    if (countdown < 0) {
        NODE_HEADER(state)->update_callback = card_boot_format_card_with_retry;
    }
}
