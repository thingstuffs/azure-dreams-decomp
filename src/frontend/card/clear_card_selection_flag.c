#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"
#include "frontend/card/server_aliases.h"
#include "frontend/card/service/operation_state_data.h"

/* Clears the card UI operation state and drains pending events. */
void clear_card_selection_flag(void) {
    card_ui_operation_state = 0;
    card_dev_drain_hw_events();
}
