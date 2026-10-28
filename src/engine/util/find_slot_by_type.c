#include "common.h"
#include "shared/actor_status.h"
#include "shared/entity.h"
#include "engine/util.h"


/* Clear the last slot of the requested type and return its value, or zero if absent. */
s32 find_slot_by_type(ActorRecord *slots, s8 type) {
    s32 slot_index;

    for (slot_index = 3; slot_index >= 0; slot_index--) {
        if (slots->status[slot_index].type == type) {
            s32 value = slots->status[slot_index].value;
            slots->status[slot_index].type = 0;
            slots->status[slot_index].value = 0;
            return value;
        }
    }
    return 0;
}
