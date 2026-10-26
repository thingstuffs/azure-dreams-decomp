#include "common.h"
#include "shared/actor_status.h"

#include "common.h"
#include "engine/message.h"
#include "shared/entity.h"


/* Clear slots of the requested type and notify the owner after each match. */
void clear_slots_of_type(ActorRecord *owner, s8 match_type)
{
    s32 slot_index;
    s8 slot_type;

    for (slot_index = 3; slot_index >= 0; slot_index--) {
        slot_type = owner->status[slot_index].type;
        if (slot_type == match_type) {
            owner->status[slot_index].type = 0;
            owner->status[slot_index].value = 0;
            end_status_effect_message(owner, match_type);
        }
    }
}
