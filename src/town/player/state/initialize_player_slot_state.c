#include "common.h"
#include "town/player/scene_action_setup.h"
#include "shared/object_index_slots.h"
#include "m2c_compat.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"
#include "town/player/state.h"
#include "town/player/motion.h"






/* Initialize the record from linked data, clear its slot flag, and reset its handler and value. */
void initialize_player_slot_state(TownObjectRecord *record, void *ptr, void *ptr2) {
    call_the_handler_selects_nonzero_entry((s32 *) ((ObjectPosition *)record->unk_44)->velocity_z, record, ptr2);
    object_index_slots[record->unk_40].unk_00 = 0;
    record->unk_04.as_pm = forward_player_motion_state;
    record->unk_10.as_s16 = 0;
}
