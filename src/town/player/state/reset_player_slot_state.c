#include "common.h"
#include "shared/object_index_slots.h"
#include "shared/town_object.h"
#include "shared/town_handler.h"


#include "shared/entity.h"
#include "shared/runtime_dispatch.h"
#include "town/player/motion.h"
#include "town/player/state.h"

/* Updates the object using its linked data, clears its slot flag, and resets its state. */
void reset_player_slot_state(TownObjectRecord *object, void *ptr, void *ptr2) {
    call_the_handler_selects_nonzero_entry(object->handler_entries[2], object, ptr2);
    object_index_slots[object->unk_40].unk_00 = 0;
    object->unk_04.as_pm = &move_player_toward_target_with_timer;
    object->unk_0A.as_s16 = 0x20;
}
