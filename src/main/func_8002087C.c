#include "common.h"
#include "m2c_compat.h"

/* cfail-repair: tf7-phase1-cache-v3 */
void card_boot_update_or_clears_selected_slot_outputs_refreshes_state_any_selected(void *state, s32 *enabled, s32 *selected);                         /* extern */

/* Passes the input value plus 0x20 to card_boot_update_or_clears_selected_slot_outputs_refreshes_state_any_selected. */
void func_8002087C(s32 value, s32 *enabled, s32 *selected) {
    card_boot_update_or_clears_selected_slot_outputs_refreshes_state_any_selected((void *)(value + 0x20), enabled, selected);
}
