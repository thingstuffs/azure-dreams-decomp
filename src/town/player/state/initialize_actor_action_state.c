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
    dispatch_sound_by_global_flag();
    state->velocity_z = 0xFFEF0000;
    call_the_handler_selects_nonzero_entry(D_800D00B0, object, (void *)(initData));
    object->unk_00 = &D_8009204C;
    object->unk_0A = 0;
}
