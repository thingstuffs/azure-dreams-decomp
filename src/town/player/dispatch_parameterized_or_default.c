#include "slus/map_state.h"
#include "common.h"
#include "m2c_compat.h"
#include "town/player.h"
#include "town/player/state.h"

/* Dispatch to the parameterized handler in state 12 or the default handler otherwise. */
void dispatch_parameterized_or_default(struct TownRectangle **entries) {
    if (map_runtime_state.scene_selector == 12) {
        initialize_state_from_terminated_entries(entries);
        return;
    }
    initialize_mode_state_tables();
}
