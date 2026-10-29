#include "common.h"
#include "m2c_compat.h"
#include "town/player.h"
#include "town/player/state.h"

extern s16 map_scene_selector_alias;

/* Dispatch to the parameterized handler in state 12 or the default handler otherwise. */
void dispatch_parameterized_or_default(s32 handler_param) {
    if (map_scene_selector_alias == 0xC) {
        initialize_state_from_terminated_entries(handler_param);
        return;
    }
    initialize_mode_state_tables();
}
