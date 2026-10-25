#include "common.h"
#include "m2c_compat.h"
#include "frontend/card.h"

/*
 * Passes the input value plus 0x20 to
 * card_boot_update_or_clears_selected_slot_outputs_refreshes_state_any_selected.
 */
void card_dev_refresh_slot_outputs(u8 *value, s32 *enabled, s32 *selected) {
    card_boot_update_or_clears_selected_slot_outputs_refreshes_state_any_selected(value + 0x20, enabled, selected);
}
