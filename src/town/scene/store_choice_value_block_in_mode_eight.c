#include "common.h"
#include "shared/town_event_state.h"
#include "town/scene.h"

s32 store_choice_value_block_in_mode_eight(TownObjectSet *context, s32 index)
{
    if (town_event_state->selection_mode == 8) {
        context->choices[index].value = prepare_stored_value_block();
        return 0;
    }
    return 1;
}
