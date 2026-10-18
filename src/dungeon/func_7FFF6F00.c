#include "modules/dungeon_ovl_16b08_local.h"

void initialize_action_callback_from_entry(ovl_16b08_local_7FFF6F00_InitState *state, void *unused, void *context) {
    call_the_handler_selects_nonzero_entry(D_800D00B8, state, context);
    state->callback = (void *)update_actor_movement_with_radial_effects;
}
