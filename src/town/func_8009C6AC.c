/* Recovered retail twin; complete-function proof is in the lane receipt. */
#include "common.h"
#include "town/player/scene_action_setup.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"
#include "town.h"
#include "town/player/motion.h"



void init_half_turn_motion_action(TownObjectRecord *object, void *unused, void *handler_context) {
    call_the_handler_selects_nonzero_entry((s32 *) ((ObjectPosition *)(object->unk_44))->velocity_z, object, handler_context);
    object_index_slots[object->unk_40].unk_00 = 0;
    object->unk_04.as_pm = forward_player_motion_state;
    object->unk_10.as_s16 = 0x800;
}
