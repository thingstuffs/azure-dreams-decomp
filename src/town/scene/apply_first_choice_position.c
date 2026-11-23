#include "common.h"
#include "town/scene/position_entries.h"
#include "town/scene.h"

void apply_first_choice_position(TownObjectSet *context, s32 type, s32 selection)
{
    apply_entry_position(first_choice_action_position_entries, first_choice_action_position_flags, context, selection);
}
