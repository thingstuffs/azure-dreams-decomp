#include "shared/town_event_state.h"
#include "common.h"
#include "town/scene.h"

s32 store_state_1_entry_value(TownObjectSet *object, s32 index, s32 unused2, s32 unused3) {
    if (town_event_state->selection_mode != 1) {
        return 1;
    }
    {
                        /* MATCH: Save store operands separately so call arguments retain their incoming registers. */
        TownObjectSet *saved_object = object;
        s32 saved_index = index;
        saved_object->choices[saved_index].value =
            prepare_stored_value_pair();
        return 0;
    }
}
