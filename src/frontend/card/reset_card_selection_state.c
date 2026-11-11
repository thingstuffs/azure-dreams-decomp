#include "common.h"
#include "frontend/card.h"
#include "frontend/card/server_aliases.h"
#include "frontend/card/server_imports.h"

/* Run setup for both indices and apply the stored value. */
void reset_card_selection_state(void) {
    invoke_callback_for_four_global_values();
    _card_wait_80408654(0);
    _card_wait_80408654(1);
    wait_selected(*(s32 *)0x804094EC);
}
