#include "shared/town_event_state.h"
#include "common.h"
#include "town/scene.h"
#include "town/scene/build_selected_entry_output_g01237.h"

/* Choice predicate: in event selection mode 7, keep the two-record value block as this choice's value. */
s32 store_two_record_block_in_mode_seven_entry(TownObjectSet *set, s32 entry_index) {
    if (town_event_state->selection_mode == 7) {
        set->choices[entry_index].value = build_two_record_value_block();
        return 0;
    }
    return 1;
}
