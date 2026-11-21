#include "common.h"
#include "frontend/card.h"
#include "frontend/card/server_aliases.h"
#include "frontend/card/server_imports.h"

/* Run setup for both indices and apply the stored value. */
void reset_card_selection_state(void) {
    card_dev_drain_hw_events();
    _card_wait_80408654(0);
    _card_wait_80408654(1);
    card_dev_wait_poll_ready(*(s32 *)0x804094EC);
}
