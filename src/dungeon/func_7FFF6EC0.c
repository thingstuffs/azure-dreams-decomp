#include "modules/dungeon_ovl_16b08_local.h"

void initialize_threshold_interaction_object(ovl_16b08_local_7FFF6EC0_InitState *state, void *unused, void *context) {
    call_the_handler_selects_nonzero_entry(D_800D0148, state, context);
    state->callback = (void *)update_threshold_object_with_interaction;
}
