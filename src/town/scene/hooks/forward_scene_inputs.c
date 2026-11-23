#include "town/scene/hooks.h"
#include "town/scene/record_actions.h"
#include "town/scene.h"

s32 forward_scene_inputs(TownObjectSet *entry, s32 entry_index) {
    return apply_selected_entry_values(entry, entry_index);
}
