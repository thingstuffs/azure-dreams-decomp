#include "common.h"
#include "town/player/scene_action_setup.h"
#include "shared/entity.h"
#include "shared/town_handler_entries.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "town/player/state.h"

#include "town/player/call_the_handler_selects_nonzero_entry_api.h"  /* extern */


/* Initializes an object and its associated state. */
void initialize_actor_action_state(TownObjectRecord *object, ObjectPosition *state, s32 initData) {
    play_sound_by_height_range();
    state->velocity_z = 0xFFEF0000;
    dispatch_selected_entry_if_nonzero(D_800D00B0, object, (void *)(initData));
    object->unk_00 = &D_8009204C;
    object->unk_0A = 0;
}
