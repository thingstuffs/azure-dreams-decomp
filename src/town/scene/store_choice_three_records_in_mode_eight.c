#include "common.h"
#include "shared/town_event_state.h"
#include "town/scene.h"
#include "town/scene/build_selected_entry_output_g01237.h"

s32 store_choice_three_records_in_mode_eight(TownObjectSet *context, s32 index)
{
    if (town_event_state->selection_mode == 8) {
        context->choices[index].value = build_three_record_value_block();
        return 0;
    }
    return 1;
}
