#include "modules/dungeon_ovl_16b08_local.h"

void initialize_actor_movement_interaction_action(ovl_16b08_local_7FFF6DBC_InitState *state, void *unused, void *context) {
    call_the_handler_selects_nonzero_entry(D_800D0128, state, context);
    state->callback = (void *)update_actor_movement_and_interaction;
}
