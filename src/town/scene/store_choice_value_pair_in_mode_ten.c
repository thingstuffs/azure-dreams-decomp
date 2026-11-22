#include "common.h"
#include "shared/town_event_state.h"
#include "town/scene.h"

s32 store_choice_value_pair_in_mode_ten(TownObjectSet *context, s32 index)
{
    if (town_event_state->selection_mode == 10) {
        context->choices[index].value = prepare_stored_value_pair();
        return 0;
    }
    return 1;
}
