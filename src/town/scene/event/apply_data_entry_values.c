#include "town/scene/record_actions.h"
#include "town/scene/entry_requests.h"
#include "town/scene.h"

s32 apply_scene_entry_values(TownObjectSet *entry, s32 entry_index) {
    return apply_selected_entry_values(entry, entry_index);
}
