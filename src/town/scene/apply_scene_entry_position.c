#include "common.h"
#include "town/scene/position_entries.h"
#include "town/scene.h"

void apply_scene_entry_position(TownObjectSet *entry, s32 type, s32 selection)
{
    apply_entry_position(sbs17_choice_position_entries, sbs17_choice_position_flags, entry, selection);
}
