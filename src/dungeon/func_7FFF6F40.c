#include "modules/dungeon_ovl_16b08_local.h"

void initialize_busy_checked_countdown_action(ovl_16b08_local_7FFF6F40_InitState *state, void *argument, void *context) {
    store_the_valid_shared_angle_in_offset_hex_10(state, argument, context);
    call_the_handler_selects_nonzero_entry(D_800D0138, state, context);
    state->callback = (void *)update_threshold_countdown_with_busy_check;
    state->count = 6;
}
