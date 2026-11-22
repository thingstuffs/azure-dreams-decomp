#include "common.h"

#include "town/scene/secondary_object_list_g00528.h"

/* Returns whether the record has attached state with type 1 or 3. */
s32 has_attached_state_type_1_or_3(TownMotionListNode *record) {
    TownMotionListNode *state;

    state = record->overlap;
    if (state == 0) {
        return 0;
    }
    if ((state->type == 1) || (state->type == 3)) {
        return 1;
    }
    return 0;
}
