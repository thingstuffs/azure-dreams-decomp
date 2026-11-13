#include "common.h"
#include "shared/entity.h"
#include "shared/town_handler_entries.h"
#include "town/player/input.h"
#include "town/player/state.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h" /* extern */
#include "town/player/position_handlers.h"



/* Initialize state and set the output pointer to the shared data. */
void initialize_input_driven_scene_object(s32 **outputData, ObjectPosition *state, s32 setupValue) {
    dispatch_sound_by_global_flag();
    state->velocity_z = 0xFFEF0000;
    dispatch_selected_entry_if_nonzero(D_800D0140, (struct TownObjectRecord *)(outputData), (void *)(setupValue));
    *outputData = update_town_object_from_input;
}
