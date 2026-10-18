#include "modules/dungeon_ovl_16b08_local.h"

void initialize_action_handler_with_count_six(ovl_16b08_local_7FFF6D14_InitState *state, void *unused, void *context) {
    call_the_handler_selects_nonzero_entry(D_800D0118, state, context);
    state->callback = (void *)dispatch_actor_interaction_with_fallback;
    state->count = 6;
}
