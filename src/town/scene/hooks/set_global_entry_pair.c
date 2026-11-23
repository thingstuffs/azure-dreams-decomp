#include "town/scene/hooks.h"
#include "town/scene/state_data.h"
#include "town/scene.h"

void set_global_entry_pair(TownObjectSet *row, s32 entry_index) {
    scene_saved_choice_row = row;
    scene_saved_choice_index = entry_index;
}
