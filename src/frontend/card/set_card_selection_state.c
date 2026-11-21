#include "common.h"
#include "frontend/card.h"
#include "frontend/card/server_imports.h"
#include "frontend/card/server_aliases.h"

/*
 * Devkit card server: settle both card channels, select the second channel (16) or the first (0), and wait on the
 * selected one.  Sibling of reset_card_selection_state (apply the stored channel) and toggle_card_selection_state
 * (switch to the other channel).
 */
void set_card_selection_state(s32 select_second)
{
    card_dev_drain_hw_events();
    _card_wait_80408654(0);
    _card_wait_80408654(1);
    if (select_second) {
        card_selected_channel = 16;
    } else {
        card_selected_channel = 0;
    }
    card_dev_wait_poll_ready(card_selected_channel);
}
