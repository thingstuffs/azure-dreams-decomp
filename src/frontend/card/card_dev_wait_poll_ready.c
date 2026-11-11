#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "frontend/card/server_aliases.h"
#include "frontend/card/server_imports.h"

/* Wait for the selected poll to succeed, then clear the pending flag and set the ready flag. */
s32 card_dev_wait_poll_ready(s32 poll_id) {
    invoke_callback_for_four_global_values();
    do {

    } while (_card_info_80408664(poll_id) == 0);
    *(s32 *)0x80409500 = 0;
    *(s32 *)0x804094E8 = 1;
    return 1;
}
