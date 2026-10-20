#include "common.h"
#include "m2c_compat.h"

void invoke_callback_for_four_global_values();                            /* extern */
s32 func_80408664();                             /* extern */

/* Wait for the selected poll to succeed, then clear the pending flag and set the ready flag. */
s32 card_dev_wait_poll_ready(s32 poll_id) {
    invoke_callback_for_four_global_values();
    do {

    } while (func_80408664(poll_id) == 0);
    *(s32 *)0x80409500 = 0;
    *(s32 *)0x804094E8 = 1;
    return 1;
}
