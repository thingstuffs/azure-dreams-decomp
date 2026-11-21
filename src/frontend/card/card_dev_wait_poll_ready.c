#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "frontend/card/server_aliases.h"
#include "frontend/card/server_imports.h"
#include "frontend/card/service/operation_state_data.h"
#include "frontend/card/service/event_mode_data.h"

/* Wait for the selected poll to succeed, then clear the pending flag and set the ready flag. */
s32 card_dev_wait_poll_ready(s32 poll_id) {
    card_dev_drain_hw_events();
    do {

    } while (_card_info_80408664(poll_id) == 0);
    card_ui_event_mode = 0;
    card_ui_operation_state = 1;
    return 1;
}
